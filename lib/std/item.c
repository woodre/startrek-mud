/* /std/item.c
 * Base item object
 */

#include "/include/mudlib.h"

private string short_desc;
private string long_desc;
private string *id_names;
private int quality;         // QUALITY_* constant
private string item_type;    // ITYPE_* constant
private int weight;          // in grams
private int value;           // in credits
private mapping stat_bonuses;// stat -> bonus amount

void create() {
    id_names = ({ });
    quality = QUALITY_COMMON;
    item_type = ITYPE_MISC;
    weight = 100;
    value = 0;
    stat_bonuses = ([ ]);
}

// ============================================================
// DESCRIPTORS
// ============================================================
void set_short(string s)      { short_desc = s; }
void set_long(string s)       { long_desc = s; }
void add_id(string s)         { id_names += ({ lower_case(s) }); }
int  id(string s)             {
    return member(id_names, lower_case(s)) != -1 ||
           (short_desc && strsrch(lower_case(short_desc), lower_case(s)) != -1);
}
string query_short()          { return short_desc; }
string query_long()           { return long_desc; }

// ============================================================
// PROPERTIES
// ============================================================
void set_quality(int q)       { quality = q; }
int  query_quality()          { return quality; }
void set_item_type(string t)  { item_type = t; }
string query_item_type()      { return item_type; }
void set_weight(int w)        { weight = w; }
int  query_weight()           { return weight; }
void set_value(int v)         { value = v; }
int  query_value()            { return value; }

// ============================================================
// STAT BONUSES
// ============================================================
void set_stat_bonus(string stat, int amount) {
    stat_bonuses[stat] = amount;
}
int query_stat_bonus(string stat) {
    if (member(stat_bonuses, stat)) return stat_bonuses[stat];
    return 0;
}
mapping query_all_stat_bonuses() { return copy(stat_bonuses); }

// ============================================================
// EQUIPPABLE? (override in weapon/armor)
// ============================================================
int is_equippable() { return 0; }
string query_slot() { return 0; }
int query_two_handed() { return 0; }

// ============================================================
// MOVE
// ============================================================
int move(mixed dest) {
    return move_object(this_object(), dest);
}

// ============================================================
// EXAMINE
// ============================================================
void examine(object viewer) {
    string quality_str = QUALITY_COLOR(quality) + QUALITY_NAME(quality) + C_RESET;
    tell_object(viewer, quality_str + " " + short_desc + "\n");
    if (long_desc)
        tell_object(viewer, wrap_string(long_desc, 70) + "\n");
    // Show stat bonuses
    string *keys = m_indices(stat_bonuses);
    if (sizeof(keys)) {
        tell_object(viewer, C_GREEN + "Item stats:\n" + C_RESET);
        foreach (string s : keys)
            tell_object(viewer, "  +" + stat_bonuses[s] + " " + cap_str(s) + "\n");
    }
    tell_object(viewer, "Sell value: " + value + " credits\n");
}
