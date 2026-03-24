inherit "/std/monster";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("a Vulcan ambassador");
    set_long("The Vulcan ambassador is a figure of serene composure, robes immaculate, hands clasped. A lifetime of logic has produced an almost preternatural calm.");
    add_id("ambassador"); add_id("vulcan"); add_id("vulcan ambassador");
    set_level(10);
    set_stat(STAT_INTELLECT, 25); set_stat(STAT_STRENGTH, 22); set_stat(STAT_SPIRIT, 18); set_stat(STAT_PRESENCE, 20);
    recalculate_derived_stats();
    set_hp(query_max_hp());
    set_xp_value(500); set_credits_value(0);
    set_faction("federation"); set_aggro(0);
}
