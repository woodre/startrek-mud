inherit "/std/room";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("Quark's Bar, Grill, Gaming House, and Holosuite Arcade");
    set_long("Quark's establishment is loud, smoky, and perpetually full. Dabo tables spin in the back. The bar serves over 200 varieties of synthehol and the real stuff for those who can afford it. Quark himself is probably somewhere, scheming. The holosuites are booked solid for the next two days.");
    set_exit("west", "/d/starfleet/rooms/main_deck");
    set_zone("Deep Space Nine");
}
