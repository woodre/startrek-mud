/* /std/armor.c
 * Armor object - inherits item.c
 */

inherit "/std/item";

#include "/include/mudlib.h"

private string armor_type;   // ATYPE_* constant
private string equip_slot;   // SLOT_* constant
private int armor_value;     // flat armor rating
private string required_class;

void create() {
    ::create();
    set_item_type(ITYPE_ARMOR);
    armor_type = ATYPE_UNIFORM;
    equip_slot = SLOT_CHEST;
    armor_value = 10;
}

int is_equippable()         { return 1; }
string query_slot()         { return equip_slot; }
int query_two_handed()      { return 0; }
string query_armor_type()   { return armor_type; }
int query_armor_value()     { return armor_value; }

void set_armor_type(string t) { armor_type = t; }
void set_equip_slot(string s) { equip_slot = s; }
void set_armor_value(int v)   {
    armor_value = v;
    set_stat_bonus(STAT_ARMOR, v);
}

// ============================================================
// EXAMINE
// ============================================================
void examine(object viewer) {
    string quality_str = QUALITY_COLOR(query_quality()) + QUALITY_NAME(query_quality()) + C_RESET;
    tell_object(viewer, quality_str + " " + query_short() + "\n");
    if (query_long())
        tell_object(viewer, wrap_string(query_long(), 70) + "\n");
    tell_object(viewer, "Type: " + cap_str(armor_type) + "  Slot: " + cap_str(equip_slot) + "\n");
    tell_object(viewer, "Armor: " + C_CYAN + armor_value + C_RESET + "\n");
    mapping bonuses = query_all_stat_bonuses();
    string *keys = m_indices(bonuses);
    if (sizeof(keys)) {
        tell_object(viewer, C_GREEN + "Stats:\n" + C_RESET);
        foreach (string s : keys)
            tell_object(viewer, "  +" + bonuses[s] + " " + cap_str(s) + "\n");
    }
    tell_object(viewer, "Value: " + query_value() + " credits\n");
}
