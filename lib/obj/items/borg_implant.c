/* Borg Neural Implant - Epic trinket */

inherit "/std/item";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("a Borg neural implant");
    set_long(
        "A recovered Borg neural implant, carefully removed from a drone by Starfleet " +
        "Medical. Most of the Collective's programming has been wiped, but the " +
        "cortical enhancement hardware remains intact. Wearing it feels deeply wrong " +
        "and profoundly effective - it accelerates cognition and threat assessment " +
        "to machine precision."
    );
    add_id("borg implant"); add_id("neural implant"); add_id("borg");
    set_quality(QUALITY_EPIC);
    set_item_type(ITYPE_TRINKET);
    set_value(8000);
    set_stat_bonus(STAT_INTELLECT,   12);
    set_stat_bonus(STAT_AGILITY,      8);
    set_stat_bonus(STAT_CRIT_CHANCE,  5);
    set_stat_bonus(STAT_HASTE,       10);
}

int is_equippable()  { return 1; }
string query_slot()  { return SLOT_TRINKET1; }
int query_two_handed(){ return 0; }
