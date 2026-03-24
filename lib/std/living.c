/* /std/living.c
 * Base living object - inherited by player.c and monster.c
 * Contains the core stat, combat, and movement systems
 */

#include "/include/mudlib.h"

// ============================================================
// VARIABLES
// ============================================================
private string living_name;
private int level;
private int hp, max_hp;
private int energy, max_energy;
private mapping primary_stats;   // str, agi, int, sta, spi, pre
private mapping secondary_stats; // crit, haste, mastery etc
private mapping equipment;       // slot -> item object
private mapping buffs;           // buff_name -> ([duration, effects])
private int in_combat;
private object combat_target;
private string race;
private string class;
private int xp;
private int xp_to_next;

// ============================================================
// INITIALIZATION
// ============================================================
void create() {
    primary_stats = ([
        STAT_STRENGTH:   10,
        STAT_AGILITY:    10,
        STAT_INTELLECT:  10,
        STAT_STAMINA:    10,
        STAT_SPIRIT:     10,
        STAT_PRESENCE:   10
    ]);
    secondary_stats = ([
        STAT_CRIT_CHANCE:  BASE_CRIT,
        STAT_HASTE:        0,
        STAT_MASTERY:      0,
        STAT_VERSATILITY:  0,
        STAT_DODGE:        BASE_DODGE,
        STAT_ARMOR:        0,
        STAT_ENERGY_REGEN: 5,
        STAT_HIT_RATING:   BASE_HIT
    ]);
    equipment = ([ ]);
    buffs = ([ ]);
    level = 1;
    race = RACE_HUMAN;
    class = CLASS_TACTICAL;
    xp = 0;
    recalculate_derived_stats();
}

// ============================================================
// STAT SYSTEM
// ============================================================

// Recalculate max HP, max energy, derived secondary stats from gear+base
void recalculate_derived_stats() {
    int sta = query_total_stat(STAT_STAMINA);
    int intel = query_total_stat(STAT_INTELLECT);
    int agi = query_total_stat(STAT_AGILITY);

    max_hp = sta * HP_PER_STAMINA + (level * 20) + 50;
    max_energy = intel * ENERGY_PER_INTELLECT + (level * 10) + 30;

    // Clamp current values
    if (hp > max_hp) hp = max_hp;
    if (energy > max_energy) energy = max_energy;
    if (!hp) hp = max_hp;
    if (!energy) energy = max_energy;

    // Recalculate secondary stats from primary
    secondary_stats[STAT_CRIT_CHANCE] = BASE_CRIT + (agi / 20);
    secondary_stats[STAT_DODGE] = BASE_DODGE + (agi / 25);
}

// Query base (unmodified) primary stat
int query_base_stat(string stat) {
    if (member(primary_stats, stat))
        return primary_stats[stat];
    return 0;
}

// Query total stat including gear bonuses and buffs
int query_total_stat(string stat) {
    int base = query_base_stat(stat);
    int gear_bonus = query_gear_stat(stat);
    int buff_bonus = query_buff_stat(stat);
    return max(1, base + gear_bonus + buff_bonus);
}

// Sum stat bonuses from all equipped items
int query_gear_stat(string stat) {
    int total = 0;
    string *slots = m_indices(equipment);
    foreach (string slot : slots) {
        object item = equipment[slot];
        if (objectp(item))
            total += item->query_stat_bonus(stat);
    }
    return total;
}

// Sum stat bonuses from active buffs
int query_buff_stat(string stat) {
    int total = 0;
    string *bnames = m_indices(buffs);
    foreach (string bname : bnames) {
        mapping buff = buffs[bname];
        if (mappingp(buff) && member(buff, stat))
            total += buff[stat];
    }
    return total;
}

// Set a base primary stat
void set_stat(string stat, int val) {
    primary_stats[stat] = max(1, val);
    recalculate_derived_stats();
}

// ============================================================
// HP AND ENERGY
// ============================================================
int query_hp()        { return hp; }
int query_max_hp()    { return max_hp; }
int query_energy()    { return energy; }
int query_max_energy(){ return max_energy; }

void set_hp(int val)     { hp = clamp(val, 0, max_hp); }
void set_energy(int val) { energy = clamp(val, 0, max_energy); }

void heal(int amount) {
    hp = clamp(hp + amount, 0, max_hp);
}

void restore_energy(int amount) {
    energy = clamp(energy + amount, 0, max_energy);
}

// Called when this living takes damage - returns actual damage taken
int take_damage(int raw_damage, string damage_type, object attacker) {
    int armor = secondary_stats[STAT_ARMOR];
    int dmg_reduction = armor / (armor + 100 + level * 10);  // Simplified armor formula
    int actual_damage = raw_damage - (raw_damage * dmg_reduction / 100);
    actual_damage = max(1, actual_damage);

    // Versatility reduces all damage taken by half its value
    int vers = secondary_stats[STAT_VERSATILITY];
    if (vers > 0)
        actual_damage -= (actual_damage * vers / 200);

    hp = max(0, hp - actual_damage);
    if (hp <= 0)
        die(attacker);
    return actual_damage;
}

// ============================================================
// COMBAT SYSTEM
// ============================================================
int is_in_combat()          { return in_combat; }
object query_combat_target(){ return combat_target; }

void enter_combat(object target) {
    in_combat = 1;
    combat_target = target;
    call_out("combat_round", COMBAT_ROUND_TIME);
}

void leave_combat() {
    in_combat = 0;
    combat_target = 0;
    remove_call_out("combat_round");
}

// Core combat round - called every COMBAT_ROUND_TIME seconds
void combat_round() {
    if (!in_combat || !objectp(combat_target)) {
        leave_combat();
        return;
    }
    if (!environment(this_object()) || environment(this_object()) != environment(combat_target)) {
        leave_combat();
        return;
    }
    if (combat_target->query_hp() <= 0) {
        leave_combat();
        return;
    }

    // Calculate attack damage
    int damage = calculate_attack_damage();

    // Check for miss
    int hit_chance = secondary_stats[STAT_HIT_RATING];
    if (random(100) >= hit_chance) {
        tell_room_combat("misses");
        call_out("combat_round", COMBAT_ROUND_TIME);
        return;
    }

    // Check for dodge
    int target_dodge = combat_target->query_secondary_stat(STAT_DODGE);
    if (random(100) < target_dodge) {
        tell_room_combat("dodged");
        call_out("combat_round", COMBAT_ROUND_TIME);
        return;
    }

    // Check for crit
    int crit_chance = secondary_stats[STAT_CRIT_CHANCE];
    int is_crit = (random(100) < crit_chance);
    if (is_crit) damage *= 2;

    // Apply versatility bonus to damage
    int vers = secondary_stats[STAT_VERSATILITY];
    if (vers > 0)
        damage += (damage * vers / 100);

    int actual = combat_target->take_damage(damage, "physical", this_object());
    tell_room_combat("hits", actual, is_crit);

    call_out("combat_round", COMBAT_ROUND_TIME);
}

int calculate_attack_damage() {
    int ap = query_total_stat(STAT_STRENGTH) * AP_PER_STRENGTH;
    int base = ap / 10 + level * 2;
    // Add weapon damage if equipped
    object weapon = equipment[SLOT_MAINHAND];
    if (!weapon) weapon = equipment[SLOT_OFFHAND];
    if (objectp(weapon))
        base += weapon->query_weapon_damage();
    return max(1, rng(base - base/4, base + base/4));
}

void tell_room_combat(string result, varargs mixed *args) {
    string tname = cap_str(living_name);
    string ename = cap_str(combat_target ? combat_target->query_name() : "someone");
    string msg;
    switch (result) {
        case "hits":
            int dmg = args[0];
            int crit = args[1];
            if (crit)
                msg = C_LRED + "*CRITICAL* " + C_RESET + tname + " strikes " + ename + " for " + C_RED + dmg + C_RESET + " damage!";
            else
                msg = tname + " strikes " + ename + " for " + C_RED + dmg + C_RESET + " damage.";
            break;
        case "misses":
            msg = tname + " swings at " + ename + " but misses!";
            break;
        case "dodged":
            msg = ename + " deftly dodges " + tname + "'s attack!";
            break;
        default:
            msg = tname + " attacks " + ename + ".";
    }
    if (environment(this_object()))
        tell_room(environment(this_object()), msg + "\n", ({ }));
}

void die(object killer) {
    in_combat = 0;
    combat_target = 0;
    remove_call_out("combat_round");
    if (environment(this_object()))
        tell_room(environment(this_object()),
            cap_str(living_name) + " has been slain!\n", ({ }));
    // Subclass handles corpse/respawn/xp
    handle_death(killer);
}

void handle_death(object killer) {
    // Override in subclass
}

// ============================================================
// EQUIPMENT SYSTEM
// ============================================================
int equip_item(object item) {
    string slot = item->query_slot();
    if (!slot) return 0;
    // Two-handed weapons occupy mainhand and offhand
    if (item->query_two_handed()) {
        unequip_slot(SLOT_OFFHAND);
        equipment[SLOT_MAINHAND] = item;
        equipment[SLOT_OFFHAND] = item;  // flag
    } else {
        // Auto-fill finger/trinket slots
        if (slot == "finger") {
            if (!equipment[SLOT_FINGER1]) slot = SLOT_FINGER1;
            else slot = SLOT_FINGER2;
        } else if (slot == "trinket") {
            if (!equipment[SLOT_TRINKET1]) slot = SLOT_TRINKET1;
            else slot = SLOT_TRINKET2;
        }
        unequip_slot(slot);
        equipment[slot] = item;
    }
    recalculate_derived_stats();
    return 1;
}

int unequip_slot(string slot) {
    if (!member(equipment, slot) || !objectp(equipment[slot])) return 0;
    object item = equipment[slot];
    map_delete(equipment, slot);
    if (objectp(item))
        item->move(this_object());
    recalculate_derived_stats();
    return 1;
}

object query_equipped(string slot) {
    if (member(equipment, slot))
        return equipment[slot];
    return 0;
}

mapping query_equipment() { return copy(equipment); }

// ============================================================
// BUFFS
// ============================================================
void add_buff(string name, mapping effects, int duration) {
    buffs[name] = effects + ([ "duration": duration ]);
    if (duration > 0)
        call_out("remove_buff", duration, name);
    recalculate_derived_stats();
}

void remove_buff(string name) {
    if (member(buffs, name))
        map_delete(buffs, name);
    recalculate_derived_stats();
}

// ============================================================
// MOVEMENT
// ============================================================
int move(mixed dest) {
    object old_env = environment(this_object());
    if (objectp(old_env))
        tell_room(old_env, cap_str(living_name) + " leaves.\n", ({ this_object() }));
    // LDMud native move
    int result = move_object(this_object(), dest);
    object new_env = environment(this_object());
    if (objectp(new_env))
        tell_room(new_env, cap_str(living_name) + " arrives.\n", ({ this_object() }));
    return result;
}

// ============================================================
// REGEN TICK (called periodically)
// ============================================================
void regen_tick() {
    if (!in_combat) {
        int spi = query_total_stat(STAT_SPIRIT);
        int hp_regen = spi * 2 + level;
        int en_regen = secondary_stats[STAT_ENERGY_REGEN] + spi;
        heal(hp_regen);
        restore_energy(en_regen);
    }
    call_out("regen_tick", 6);
}

// ============================================================
// LEVEL SYSTEM
// ============================================================
int query_level() { return level; }

void gain_xp(int amount) {
    xp += amount;
    while (xp >= xp_to_next && level < MAX_LEVEL)
        level_up();
}

void level_up() {
    xp -= xp_to_next;
    level++;
    xp_to_next = xp_for_level(level + 1);
    // Grant stat points on level up
    string *stats = ALL_PRIMARY_STATS;
    foreach (string s : stats)
        primary_stats[s] += LEVEL_STAT_BONUS;
    recalculate_derived_stats();
    hp = max_hp;
    energy = max_energy;
    if (IS_PLAYER(this_object()))
        tell_object(this_object(),
            C_LYELLOW + "\n*** You have reached level " + level + "! ***\n" + C_RESET);
}

// ============================================================
// BASIC ACCESSORS
// ============================================================
string query_name()     { return living_name; }
void   set_name(string n){ living_name = n; }
string query_race()     { return race; }
void   set_race(string r){ race = r; }
string query_class()    { return class; }
void   set_class(string c){ class = c; }
int    query_xp()       { return xp; }
int    query_xp_to_next(){ return xp_to_next; }
int    query_secondary_stat(string s) {
    if (member(secondary_stats, s)) return secondary_stats[s];
    return 0;
}

int is_player() { return 0; }
int is_monster(){ return 0; }
