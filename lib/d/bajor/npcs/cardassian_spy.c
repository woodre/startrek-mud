/* Cardassian spy - hostile, level 6 */

inherit "/std/monster";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("a Cardassian spy");
    set_long("Dressed in plain clothing that doesn't quite conceal the rigid neck scales of a Cardassian, this spy watches everything with calculating gray eyes. They don't look pleased to have been noticed.");
    add_id("spy"); add_id("cardassian"); add_id("cardassian spy");
    set_level(6);
    set_stat(STAT_INTELLECT, 20); set_stat(STAT_STRENGTH, 17);
    set_stat(STAT_AGILITY, 15);  set_stat(STAT_STAMINA, 16);
    recalculate_derived_stats();
    set_hp(query_max_hp());
    set_xp_value(350); set_credits_value(40);
    set_faction("cardassian"); set_aggro(1);
    add_loot("/d/starfleet/items/type1_phaser");
}
