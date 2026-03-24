inherit "/std/monster";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("a Bajoran monk");
    set_long("A Bajoran monk in flowing earthen robes, a Bajoran earring hanging from the right ear. They move with quiet grace, tending to the temple incense burners.");
    add_id("monk"); add_id("bajoran monk"); add_id("bajoran");
    set_level(3);
    set_stat(STAT_SPIRIT, 20); set_stat(STAT_PRESENCE, 18); set_stat(STAT_INTELLECT, 15);
    recalculate_derived_stats();
    set_hp(query_max_hp());
    set_xp_value(0); set_credits_value(0);
    set_faction("bajoran"); set_aggro(0);
}
