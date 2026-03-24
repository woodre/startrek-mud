/* Security Cadet - Level 3 fighter */

inherit "/std/monster";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("a security cadet");
    set_long("A Starfleet security cadet in a gold-shouldered uniform, tense and alert. " +
             "She grips a Type-2 phaser training replica and watches the training floor " +
             "with focused intensity.");
    add_id("security cadet");
    add_id("cadet");
    add_id("security");
    set_level(3);
    set_stat(STAT_STRENGTH, 15);
    set_stat(STAT_AGILITY, 13);
    set_stat(STAT_STAMINA, 14);
    set_stat(STAT_INTELLECT, 10);
    recalculate_derived_stats();
    set_hp(query_max_hp());
    set_xp_value(150);
    set_credits_value(5);
    set_faction("federation");
    set_aggro(0);
    add_loot("/d/starfleet/items/type1_phaser");
}
