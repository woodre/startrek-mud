inherit "/std/monster";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("a Klingon warrior");
    set_long("A hulking Klingon warrior, armor scarred from countless battles. The ridge on his forehead is pronounced, his eyes burning with the fire of someone who welcomes a good fight.");
    add_id("klingon"); add_id("warrior"); add_id("klingon warrior");
    set_level(5);
    set_stat(STAT_STRENGTH, 22); set_stat(STAT_STAMINA, 20); set_stat(STAT_AGILITY, 14);
    recalculate_derived_stats();
    set_hp(query_max_hp());
    set_xp_value(200); set_credits_value(15);
    set_faction("klingon"); set_aggro(1);
    add_loot("/d/klingon/items/mekleth");
    add_loot("/d/klingon/items/warrior_armor");
}
