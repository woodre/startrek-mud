/* Security Combat Vest - Uncommon quality chest armor */

inherit "/std/armor";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("a security combat vest");
    set_long("A reinforced Starfleet security combat vest in tactical gray. " +
             "Multiple pockets hold power cells and field equipment. The duranium " +
             "composite plating covers the vital areas. Preferred by tactical officers.");
    add_id("combat vest"); add_id("vest"); add_id("security vest");
    set_quality(QUALITY_UNCOMMON);
    set_armor_type(ATYPE_MEDIUM);
    set_equip_slot(SLOT_CHEST);
    set_armor_value(40);
    set_value(200);
    set_stat_bonus(STAT_STAMINA, 5);
    set_stat_bonus(STAT_STRENGTH, 3);
}
