/* Starfleet Phaser Rifle - Rare quality, 2H ranged */

inherit "/std/weapon";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("a Starfleet phaser rifle");
    set_long("A heavy-duty Starfleet phaser rifle, designed for combat situations " +
             "requiring maximum firepower. The targeting scope is integrated into the " +
             "stock. Requires both hands to operate effectively.");
    add_id("phaser rifle"); add_id("rifle");
    set_quality(QUALITY_RARE);
    set_weapon_type(WTYPE_PHASER_RIFLE);
    set_damage(20, 35);
    set_value(800);
    set_stat_bonus(STAT_AGILITY, 8);
    set_stat_bonus(STAT_STRENGTH, 5);
    set_stat_bonus(STAT_CRIT_CHANCE, 3);
}
