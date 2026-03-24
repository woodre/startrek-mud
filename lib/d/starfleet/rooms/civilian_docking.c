inherit "/std/room";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("Civilian Docking Area");
    set_long("The civilian docking section is a constant low-level bustle. Freighters offload cargo. Shuttle pilots haggle over berth fees. Travellers from a dozen worlds lug baggage toward customs. A large status board shows arrival and departure schedules.");
    set_exit("north", "/d/starfleet/rooms/academy_entrance");
    set_exit("east",  "/d/starfleet/rooms/main_deck");
    set_zone("Deep Space Nine");
}
