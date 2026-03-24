inherit "/std/monster";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("a Bajoran security guard");
    set_long("A Bajoran officer in a Starfleet/Bajoran Militia hybrid uniform patrols with a calm but watchful demeanor. The ridges on their nose are distinctive.");
    add_id("bajoran guard"); add_id("guard"); add_id("bajoran");
    set_level(4);
    set_stat(STAT_STRENGTH, 16); set_stat(STAT_AGILITY, 14); set_stat(STAT_STAMINA, 15);
    recalculate_derived_stats();
    set_hp(query_max_hp());
    set_xp_value(120); set_credits_value(8);
    set_faction("federation"); set_aggro(0);
}
