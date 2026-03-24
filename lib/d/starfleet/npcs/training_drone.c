/* Training Drone - Level 1 combat target for new players */

inherit "/std/monster";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("a Starfleet training drone");
    set_long("A spherical Mark-IV holographic training drone hovers at chest height, " +
             "its surface covered in sensor nodes and a single low-power stun emitter. " +
             "A green status light blinks steadily.");
    add_id("drone");
    add_id("training drone");
    add_id("holodrone");
    set_level(1);
    set_stat(STAT_STRENGTH, 8);
    set_stat(STAT_AGILITY, 12);
    set_stat(STAT_STAMINA, 10);
    recalculate_derived_stats();
    set_hp(query_max_hp());
    set_xp_value(50);
    set_credits_value(0);
    set_faction("neutral");
    set_aggro(0);  // only attacks if attacked
    set_race("construct");
}
