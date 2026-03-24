/* The Sword of Kahless - Legendary 2H melee weapon */

inherit "/std/weapon";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("the Sword of Kahless");
    set_long(
        "The legendary bat'leth of Kahless the Unforgettable himself, recovered from the " +
        "Gamma Quadrant. The blade radiates a faint crimson glow as if remembering every " +
        "battle it has won. Engravings in Old Klingon run along the inner curve: " +
        "'With this sword I will lead your people to the gates of Sto-Vo-Kor.' " +
        "To hold it is to feel the weight of Klingon history in your hands."
    );
    add_id("sword of kahless"); add_id("kahless sword"); add_id("legendary bat'leth");
    set_quality(QUALITY_LEGENDARY);
    set_weapon_type(WTYPE_BATLET);
    set_damage(60, 90);
    set_value(50000);
    set_stat_bonus(STAT_STRENGTH,    20);
    set_stat_bonus(STAT_STAMINA,     15);
    set_stat_bonus(STAT_AGILITY,     10);
    set_stat_bonus(STAT_CRIT_CHANCE,  8);
    set_stat_bonus(STAT_MASTERY,     12);
    set_stat_bonus(STAT_VERSATILITY,  5);
}
