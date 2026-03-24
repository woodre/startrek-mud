/* Starfleet Academy - Tactical Training Wing */

inherit "/std/room";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("Starfleet Academy - Tactical Training Wing");
    set_long(
        "The Tactical Training Wing is a hardened bunker beneath the Academy grounds. " +
        "Combat holoemitters line every wall, capable of projecting any known hostile " +
        "environment at a moment's notice. Phaser racks are bolted along the south wall, " +
        "a mix of Type-1 and Type-2 phasers in charging cradles. Drill Sergeant T'Vok " +
        "runs recruits through hand-to-hand combat sequences with unyielding precision. " +
        "Signs warn: LIVE FIRE EXERCISES IN PROGRESS - SAFETY PROTOCOLS ENFORCED."
    );
    set_exit("west",  "/d/starfleet/rooms/academy_quad");
    set_exit("north", "/d/starfleet/rooms/holodeck_one");
    set_zone("Starfleet Academy");
}

void reset() {
    // Spawn a Security Cadet enemy
    object ob = first_inventory(this_object());
    int found = 0;
    while (ob) {
        if (!IS_PLAYER(ob) && living(ob) && strsrch(ob->query_name(), "security") != -1)
            { found = 1; break; }
        ob = next_inventory(ob);
    }
    if (!found) {
        object sec = clone_object("/d/starfleet/npcs/security_cadet");
        sec->move(this_object());
    }
    // Spawn a Type-2 Phaser item
    ob = first_inventory(this_object());
    found = 0;
    while (ob) {
        if (!living(ob) && ob->id("phaser")) { found = 1; break; }
        ob = next_inventory(ob);
    }
    if (!found) {
        object phaser = clone_object("/d/starfleet/items/type2_phaser");
        phaser->move(this_object());
    }
}
