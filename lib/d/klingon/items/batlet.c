/* Klingon Bat'leth - Uncommon 2H melee weapon */

inherit "/std/weapon";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("a Klingon bat'leth");
    set_long("The legendary bat'leth - the Sword of Honor - forged in the tradition of " +
             "Kahless himself. The crescent blade with its two protruding handles is " +
             "a weapon that demands both skill and strength. To wield it is to carry " +
             "the honor of every Klingon warrior who came before.");
    add_id("bat'leth"); add_id("batleth"); add_id("sword of honor"); add_id("batlet");
    set_quality(QUALITY_UNCOMMON);
    set_weapon_type(WTYPE_BATLET);
    set_damage(22, 35);
    set_value(500);
    set_stat_bonus(STAT_STRENGTH, 10);
    set_stat_bonus(STAT_STAMINA, 5);
    set_stat_bonus(STAT_CRIT_CHANCE, 2);
}
