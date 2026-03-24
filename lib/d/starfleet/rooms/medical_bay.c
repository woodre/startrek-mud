/* Starfleet Medical Bay - Respawn point */

inherit "/std/room";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("Starfleet Medical Bay");
    set_long(
        "The sterile white walls of Starfleet Medical Bay are lined with biobeds, each " +
        "equipped with a humming biofunction monitor. The soft blue glow of medical " +
        "tricorders gives the room an ethereal quality. Dr. Crusher's holographic " +
        "assistant moves efficiently between beds. The antiseptic smell of " +
        "triox compound lingers in the recycled air. A large viewport shows the " +
        "Academy grounds outside. This is where the injured and the fallen are brought " +
        "back to health."
    );
    set_exit("west",  "/d/starfleet/rooms/academy_entrance");
    set_exit("north", "/d/starfleet/rooms/academy_quad");
    set_zone("Starfleet Academy");
}

void reset() {
    object ob = first_inventory(this_object());
    int found = 0;
    while (ob) {
        if (!IS_PLAYER(ob) && living(ob) && strsrch(ob->query_name(), "medic") != -1)
            { found = 1; break; }
        ob = next_inventory(ob);
    }
    if (!found) {
        object medic = clone_object("/d/starfleet/npcs/medic");
        medic->move(this_object());
    }
}
