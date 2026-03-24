/* Deep Space Nine - Ops Center */

inherit "/std/room";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("Deep Space Nine - Ops Center");
    set_long(
        "The Ops Center is the nerve center of Deep Space Nine. LCARS displays ring the " +
        "upper and lower tiers, showing sensor feeds, power distribution grids, and " +
        "incoming subspace comm traffic. Commander Sisko's office door is visible on " +
        "the upper level behind a railing. At the central console, a Starfleet officer " +
        "monitors the station's systems with practiced efficiency. A large viewscreen " +
        "currently shows a tactical map of the Bajoran system. The turbolift to the " +
        "docking pylons is along the east wall."
    );
    set_exit("south", "/d/starfleet/rooms/main_deck");
    set_exit("east",  "/d/starfleet/rooms/tactical_wing");
    set_zone("Deep Space Nine");
}

void reset() {
    object ob = first_inventory(this_object());
    int found = 0;
    while (ob) {
        if (!IS_PLAYER(ob) && living(ob)) { found = 1; break; }
        ob = next_inventory(ob);
    }
    if (!found) {
        object off = clone_object("/d/starfleet/npcs/starfleet_officer");
        off->move(this_object());
    }
}
