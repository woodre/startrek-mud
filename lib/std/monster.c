/* /std/monster.c
 * NPC / Monster object - inherits living.c
 */

inherit "/std/living";

#include "/include/mudlib.h"

private string short_desc;
private string long_desc;
private string *id_names;
private int xp_value;
private int credits_value;   // Star Trek currency
private string *loot_table;  // file paths of items to drop
private string faction;      // "federation", "klingon", "romulan", "borg", "neutral"
private int aggro;           // 1 = attacks players on sight
private int wander;          // 1 = randomly moves through rooms
private int is_alive;

void create() {
    ::create();
    id_names = ({ });
    loot_table = ({ });
    faction = "neutral";
    aggro = 0;
    wander = 0;
    xp_value = 50;
    credits_value = 10;
    is_alive = 1;
    call_out("ai_tick", 5);
}

int is_monster() { return 1; }
int is_alive()   { return is_alive; }

// ============================================================
// DESCRIPTORS
// ============================================================
void set_short(string s)    { short_desc = s; set_name(s); }
void set_long(string s)     { long_desc = s; }
string query_short()        { return short_desc; }
string query_long()         { return long_desc; }
void add_id(string s)       { id_names += ({ s }); }
int  id(string s)           {
    return member(id_names, lower_case(s)) != -1 ||
           strsrch(lower_case(short_desc), lower_case(s)) != -1;
}
void set_faction(string f)  { faction = f; }
string query_faction()      { return faction; }
void set_aggro(int a)       { aggro = a; }
void set_wander(int w)      { wander = w; }
void set_xp_value(int x)    { xp_value = x; }
void set_credits_value(int c){ credits_value = c; }
void add_loot(string path)  { loot_table += ({ path }); }

// ============================================================
// EXAMINE
// ============================================================
void examine(object viewer) {
    tell_object(viewer, C_WHITE + cap_str(short_desc) + C_RESET + "\n");
    if (long_desc)
        tell_object(viewer, wrap_string(long_desc, 70) + "\n");
    // Show health estimate
    int pct = percent(query_hp(), query_max_hp());
    string condition;
    if (pct >= 90)      condition = C_LGREEN + "is in perfect health";
    else if (pct >= 70) condition = C_GREEN  + "has minor wounds";
    else if (pct >= 40) condition = C_YELLOW + "is moderately wounded";
    else if (pct >= 20) condition = C_LRED   + "is badly wounded";
    else                condition = C_RED    + "is near death";
    tell_object(viewer, cap_str(short_desc) + " " + condition + C_RESET + ".\n");
    tell_object(viewer, "Level: " + query_level() + "\n");
}

// ============================================================
// AI TICK
// ============================================================
void ai_tick() {
    if (!is_alive) return;
    object env = environment(this_object());
    if (!env) { call_out("ai_tick", 5); return; }

    // Aggro: scan for players to attack
    if (aggro && !is_in_combat()) {
        object ob = first_inventory(env);
        while (ob) {
            if (IS_PLAYER(ob) && ob->query_hp() > 0) {
                enter_combat(ob);
                ob->enter_combat(this_object());
                tell_room(env,
                    C_LRED + cap_str(query_name()) + " attacks " +
                    cap_str(ob->query_name()) + "!\n" + C_RESET,
                    ({ }));
                break;
            }
            ob = next_inventory(ob);
        }
    }

    // Wander: random movement when not in combat
    if (wander && !is_in_combat()) {
        if (random(4) == 0) {
            mapping exits = env->query_exits();
            if (exits && sizeof(exits)) {
                string dir = m_indices(exits)[random(sizeof(exits))];
                string dest = exits[dir];
                move(dest);
            }
        }
    }

    call_out("ai_tick", 5);
}

// ============================================================
// INIT (for monsters to add combat commands if needed)
// ============================================================
void init() {
    // Monsters can add actions here
}

// ============================================================
// DEATH
// ============================================================
void handle_death(object killer) {
    is_alive = 0;
    remove_call_out("ai_tick");
    leave_combat();

    // Award XP and notify killer
    if (objectp(killer) && IS_PLAYER(killer)) {
        killer->gain_xp(xp_value);
        tell_object(killer, C_LYELLOW + "You gain " + xp_value + " experience points.\n" + C_RESET);
    }

    // Drop loot
    drop_loot();

    // Create corpse
    object corpse = clone_object("/obj/corpse");
    corpse->setup(query_name(), credits_value);
    object corpse_env = environment(this_object());
    if (!corpse_env) corpse_env = environment(killer);
    if (corpse_env) corpse->move(corpse_env);

    // Respawn after delay
    call_out("respawn", 60);
    move("/");  // Move to void (remove from room)
}

void drop_loot() {
    object env = environment(this_object());
    if (!env) return;
    foreach (string path : loot_table) {
        if (random(100) < 40) {  // 40% drop chance per item
            object item = clone_object(path);
            item->move(env);
        }
    }
}

void respawn() {
    is_alive = 1;
    set_hp(query_max_hp());
    set_energy(query_max_energy());
    // Move back to our home room (stored at creation)
    // For now, rooms handle this via their reset() function
    call_out("ai_tick", 5);
}
