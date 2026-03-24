/* Deep Space 9 - Main Deck (DS9 Hub) */

inherit "/std/room";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("Deep Space Nine - Promenade Level");
    set_long(
        "The Promenade of Deep Space Nine hums with activity. Bajoran workers, Federation " +
        "officers, Ferengi merchants, and alien travelers of dozens of species crowd the " +
        "curved corridor. Quark's Bar spills warm, noisy light from its entrance to the " +
        "east. The Infirmary is to the west. Above, the second level walkway overlooks " +
        "the bustle below. Viewports in the outer ring show the brilliant nebula of the " +
        "Bajoran system. A sign reads: WELCOME TO DEEP SPACE NINE - GATEWAY TO THE " +
        "GAMMA QUADRANT. The station feels alive with opportunity and barely-controlled chaos."
    );
    set_exit("north", "/d/starfleet/rooms/ops_center");
    set_exit("south", "/d/bajor/rooms/temple_entrance");
    set_exit("east",  "/d/starfleet/rooms/quarks_bar");
    set_exit("west",  "/d/starfleet/rooms/medical_bay");
    set_exit("up",    "/d/starfleet/rooms/academy_entrance");
    set_exit("down",  "/d/space/rooms/docking_ring");
    set_zone("Deep Space Nine");
}

void reset() {
    // Spawn a Bajoran guard
    object ob = first_inventory(this_object());
    int found = 0;
    while (ob) {
        if (!IS_PLAYER(ob) && living(ob)) { found = 1; break; }
        ob = next_inventory(ob);
    }
    if (!found) {
        object guard = clone_object("/d/starfleet/npcs/bajoran_guard");
        guard->move(this_object());
    }
}
