inherit "/std/room";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("DS9 - Outer Docking Ring");
    set_long("The docking ring is a vast, zero-gravity corridor arcing around the outer edge of DS9. Airlock doors line the curved wall at regular intervals, each leading to a docked vessel. Through the viewport, the Bajoran sun is a distant orange point. Runabout Pad A is to the east.");
    set_exit("up",   "/d/starfleet/rooms/main_deck");
    set_exit("east", "/d/space/rooms/runabout_pad");
    set_zone("Deep Space Nine Exterior");
}
