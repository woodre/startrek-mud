/* Vulcan Embassy Quarter */

inherit "/std/room";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("Vulcan Embassy - Meditation Chambers");
    set_long(
        "The Vulcan section of the station is an oasis of austere calm. The air is kept " +
        "warmer and drier than the rest of the Promenade, in keeping with Vulcan " +
        "preference. Low incense burners emit pale smoke that drifts in elegant spirals. " +
        "Wall panels display IDIC symbols and Vulcan calligraphy. A senior ambassador " +
        "in traditional robes meditates on a raised dais at the chamber's center. " +
        "A display case holds a ceremonial lirpa and mek'leth, artifacts of cultural " +
        "exchange. New Vulcan characters begin their journey here."
    );
    set_exit("south", "/d/starfleet/rooms/science_wing");
    set_exit("east",  "/d/starfleet/rooms/main_deck");
    set_zone("Vulcan Quarter");
}

void reset() {
    object ob = first_inventory(this_object());
    int found = 0;
    while (ob) {
        if (!IS_PLAYER(ob) && living(ob)) { found = 1; break; }
        ob = next_inventory(ob);
    }
    if (!found) {
        object amb = clone_object("/d/starfleet/npcs/vulcan_ambassador");
        amb->move(this_object());
    }
}
