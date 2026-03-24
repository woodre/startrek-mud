inherit "/std/monster";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("a battle targ");
    set_long("A battle targ - a fierce Klingon beast the size of a large dog, covered in dark bristled fur with six legs and a jaw full of serrated teeth. Its eyes glow red.");
    add_id("targ"); add_id("battle targ");
    set_level(2);
    set_stat(STAT_STRENGTH, 14); set_stat(STAT_AGILITY, 16); set_stat(STAT_STAMINA, 12);
    recalculate_derived_stats();
    set_hp(query_max_hp());
    set_xp_value(75); set_credits_value(5);
    set_faction("klingon"); set_aggro(1); set_wander(1);
    add_loot("/d/klingon/items/targ_hide");
}
