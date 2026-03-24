inherit "/std/monster";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("a Starfleet officer");
    set_long("A seasoned Starfleet officer, pips glinting on the collar, eyes sharp with years of experience across the quadrant.");
    add_id("officer"); add_id("starfleet officer");
    set_level(8);
    set_stat(STAT_STRENGTH, 18); set_stat(STAT_INTELLECT, 17); set_stat(STAT_STAMINA, 16); set_stat(STAT_PRESENCE, 15);
    recalculate_derived_stats();
    set_hp(query_max_hp());
    set_xp_value(300); set_credits_value(25);
    set_faction("federation"); set_aggro(0);
}
