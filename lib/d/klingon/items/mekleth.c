/* Klingon Mek'leth - Common melee weapon */

inherit "/std/weapon";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("a Klingon mek'leth");
    set_long("A Klingon mek'leth - a curved, double-edged blade roughly half a meter " +
             "long. The grip is wrapped in targ leather, worn from use. The blade's " +
             "edge is honed to a mirror finish despite the battle scratches on the flat.");
    add_id("mekleth"); add_id("mek'leth"); add_id("klingon blade"); add_id("blade");
    set_quality(QUALITY_COMMON);
    set_weapon_type(WTYPE_MEKLETH);
    set_damage(10, 18);
    set_value(120);
    set_stat_bonus(STAT_STRENGTH, 5);
    set_stat_bonus(STAT_AGILITY, 2);
}
