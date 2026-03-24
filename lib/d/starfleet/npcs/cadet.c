/* Generic Starfleet Cadet NPC */

inherit "/std/monster";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("a Starfleet cadet");
    set_long("A young Starfleet cadet, uniform crisp, eyes wide with the mix of " +
             "excitement and nervousness that marks every first-year officer.");
    add_id("cadet");
    add_id("starfleet cadet");
    set_level(1);
    set_stat(STAT_STRENGTH, 9);
    set_stat(STAT_AGILITY, 9);
    set_stat(STAT_STAMINA, 9);
    recalculate_derived_stats();
    set_hp(query_max_hp());
    set_xp_value(25);
    set_credits_value(2);
    set_faction("federation");
    set_aggro(0);
}
