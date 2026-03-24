/* /std/weapon.c
 * Weapon object - inherits item.c
 */

inherit "/std/item";

#include "/include/mudlib.h"

private string weapon_type;  // WTYPE_* constant
private int min_damage;
private int max_damage;
private string damage_type;  // "physical", "energy", "psionic"
private int two_handed;
private string equip_slot;   // SLOT_MAINHAND or SLOT_RANGED
private int attack_speed;    // milliseconds between attacks (lower=faster)
private string required_class;

void create() {
    ::create();
    set_item_type(ITYPE_WEAPON);
    weapon_type = WTYPE_PHASER;
    min_damage = 5;
    max_damage = 10;
    damage_type = "energy";
    two_handed = 0;
    equip_slot = SLOT_MAINHAND;
    attack_speed = 2000;
}

int is_equippable()         { return 1; }
string query_slot()         { return equip_slot; }
int query_two_handed()      { return two_handed; }
string query_weapon_type()  { return weapon_type; }
string query_damage_type()  { return damage_type; }
int query_attack_speed()    { return attack_speed; }

void set_weapon_type(string t) {
    weapon_type = t;
    // Auto-set properties based on type
    switch (t) {
        case WTYPE_PHASER:
            equip_slot = SLOT_MAINHAND; two_handed = 0;
            damage_type = "energy"; break;
        case WTYPE_PHASER_RIFLE:
            equip_slot = SLOT_RANGED; two_handed = 1;
            damage_type = "energy"; break;
        case WTYPE_DISRUPTOR:
            equip_slot = SLOT_MAINHAND; two_handed = 0;
            damage_type = "energy"; break;
        case WTYPE_BATLET:
            equip_slot = SLOT_MAINHAND; two_handed = 1;
            damage_type = "physical"; break;
        case WTYPE_MEKLETH:
            equip_slot = SLOT_MAINHAND; two_handed = 0;
            damage_type = "physical"; break;
        case WTYPE_LIRPA:
            equip_slot = SLOT_MAINHAND; two_handed = 1;
            damage_type = "physical"; break;
        case WTYPE_USHAAN_TOR:
            equip_slot = SLOT_MAINHAND; two_handed = 0;
            damage_type = "physical"; break;
        case WTYPE_STAFF:
            equip_slot = SLOT_MAINHAND; two_handed = 1;
            damage_type = "psionic"; break;
        default:
            equip_slot = SLOT_MAINHAND; two_handed = 0;
            damage_type = "physical"; break;
    }
}

void set_damage(int minval, int maxval) {
    min_damage = minval;
    max_damage = maxval;
}

int query_weapon_damage() {
    return rng(min_damage, max_damage);
}

// ============================================================
// EXAMINE
// ============================================================
void examine(object viewer) {
    string quality_str = QUALITY_COLOR(query_quality()) + QUALITY_NAME(query_quality()) + C_RESET;
    tell_object(viewer, quality_str + " " + query_short() + "\n");
    if (query_long())
        tell_object(viewer, wrap_string(query_long(), 70) + "\n");
    tell_object(viewer, "Type: " + cap_str(weapon_type) + "  Slot: " + cap_str(equip_slot) + "\n");
    tell_object(viewer, "Damage: " + C_LRED + min_damage + "-" + max_damage + C_RESET +
                        "  Type: " + cap_str(damage_type) + "\n");
    if (two_handed)
        tell_object(viewer, C_YELLOW + "Two-handed\n" + C_RESET);
    // Stat bonuses
    mapping bonuses = query_all_stat_bonuses();
    string *keys = m_indices(bonuses);
    if (sizeof(keys)) {
        tell_object(viewer, C_GREEN + "Stats:\n" + C_RESET);
        foreach (string s : keys)
            tell_object(viewer, "  +" + bonuses[s] + " " + cap_str(s) + "\n");
    }
    tell_object(viewer, "Value: " + query_value() + " credits\n");
}
