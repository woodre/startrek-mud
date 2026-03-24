/* Type-1 Phaser - Basic sidearm, Common quality */

inherit "/std/weapon";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("a Type-1 phaser");
    set_long("A sleek, palm-sized Federation Type-1 phaser. Compact enough to conceal, " +
             "it trades raw power for discretion. The safety toggle is on the side.");
    add_id("type-1 phaser"); add_id("type1 phaser"); add_id("phaser"); add_id("type 1");
    set_quality(QUALITY_COMMON);
    set_weapon_type(WTYPE_PHASER);
    set_damage(4, 8);
    set_value(50);
    set_stat_bonus(STAT_AGILITY, 2);
}
