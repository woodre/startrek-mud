inherit "/std/room";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("Starfleet Academy - Observation Tower");
    set_long("From the top of the tower, you can see the sweep of San Francisco Bay below and the golden span of the old Golden Gate Bridge. The city skyline glitters. Beyond, the Pacific stretches to the horizon. It is impossible to look at this view and not feel the pull of what lies beyond the stars.");
    set_exit("down", "/d/starfleet/rooms/academy_quad");
    set_zone("Starfleet Academy");
}
