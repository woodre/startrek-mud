inherit "/std/room";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("Runabout Pad A");
    set_long("Runabout Pad A holds the USS Rio Grande, a compact Danube-class runabout. The pilot seat and two mission seats are visible through the open hatch. The pad controls allow mission assignment and departure sequencing. The wormhole is a shimmer on the viewscreen to the east.");
    set_exit("west", "/d/space/rooms/docking_ring");
    set_zone("Deep Space Nine Exterior");
}
