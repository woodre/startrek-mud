/* Orb of Time - Legendary Trinket */

inherit "/std/item";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("the Orb of Time");
    set_long(
        "One of the nine Tears of the Prophets - the Orb of Time. An hourglass-shaped " +
        "artifact that glows with a shifting, prismatic light that seems to move " +
        "against time itself. Those who look into it too long see flashes of their " +
        "own past and possible futures. The Bajoran Prophets placed this among the " +
        "corporeal world for reasons only they understand."
    );
    add_id("orb of time"); add_id("orb"); add_id("tear of the prophets");
    set_quality(QUALITY_LEGENDARY);
    set_item_type(ITYPE_TRINKET);
    set_equip_slot := "trinket";
    set_value(100000);
    set_stat_bonus(STAT_INTELLECT,   18);
    set_stat_bonus(STAT_SPIRIT,      15);
    set_stat_bonus(STAT_PRESENCE,    12);
    set_stat_bonus(STAT_HASTE,       20);
    set_stat_bonus(STAT_MASTERY,     15);
}

// Trinkets are equippable
int is_equippable()  { return 1; }
string query_slot()  { return SLOT_TRINKET1; }
int query_two_handed(){ return 0; }
