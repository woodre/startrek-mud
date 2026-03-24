inherit "/std/monster";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("a science cadet");
    set_long("A bright-eyed science cadet in Sciences blue, forever scribbling notes on a data padd and asking questions no one else thinks to ask.");
    add_id("science cadet"); add_id("cadet"); add_id("science");
    set_level(2);
    set_stat(STAT_INTELLECT, 15); set_stat(STAT_SPIRIT, 13); set_stat(STAT_STAMINA, 9);
    recalculate_derived_stats();
    set_hp(query_max_hp());
    set_xp_value(60); set_credits_value(3);
    set_faction("federation"); set_aggro(0);
}
