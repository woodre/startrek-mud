/* Starfleet Medic NPC */

inherit "/std/monster";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("a Starfleet medic");
    set_long("A calm, professional medic in Sciences blue, medical tricorder clipped " +
             "to one hip and a hypospray in hand. She's seen it all and remains unflappable.");
    add_id("medic");
    add_id("doctor");
    add_id("starfleet medic");
    set_level(5);
    set_stat(STAT_INTELLECT, 20);
    set_stat(STAT_SPIRIT, 18);
    set_stat(STAT_STAMINA, 12);
    recalculate_derived_stats();
    set_hp(query_max_hp());
    set_xp_value(0);   // Don't award XP for killing the medic
    set_credits_value(0);
    set_faction("federation");
    set_aggro(0);
}

void init() {
    ::init();
    add_action("cmd_heal", "heal");
    add_action("cmd_heal", "revive");
}

int cmd_heal(string arg) {
    object player = this_player();
    if (!IS_PLAYER(player)) return 0;
    if (player->query_hp() >= player->query_max_hp()) {
        tell_object(player, "The medic scans you. \"You're in perfect health, " +
                    player->query_name() + ".\"\n");
        return 1;
    }
    int heal_amount = player->query_max_hp() - player->query_hp();
    player->heal(heal_amount);
    tell_object(player, "The medic applies a hypospray. You feel refreshed. " +
                "\"Rest up, " + player->query_name() + ".\"\n");
    tell_room(environment(this_object()),
        "The medic heals " + cap_str(player->query_name()) + ".\n",
        ({ player }));
    return 1;
}
