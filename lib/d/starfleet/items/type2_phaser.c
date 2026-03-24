/* Type-2 Phaser - Standard sidearm, Uncommon quality */

inherit "/std/weapon";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("a Type-2 phaser");
    set_long("The standard-issue Starfleet Type-2 phaser. Ergonomically designed with " +
             "16 settings from stun to full disintegration. A familiar weight in the hand of " +
             "any Starfleet officer.");
    add_id("type-2 phaser"); add_id("type2 phaser"); add_id("phaser"); add_id("type 2");
    set_quality(QUALITY_UNCOMMON);
    set_weapon_type(WTYPE_PHASER);
    set_damage(8, 16);
    set_value(150);
    set_stat_bonus(STAT_AGILITY, 4);
    set_stat_bonus(STAT_STRENGTH, 2);
}
