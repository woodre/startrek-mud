inherit "/std/room";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("Holodeck One");
    set_long("The holodeck is currently displaying a generic grid pattern of yellow lines on black. The ARCH console to the side shows a menu of 47 available programs. The smell of ozone hints at recent heavy use.");
    set_exit("south", "/d/starfleet/rooms/tactical_wing");
    set_zone("Starfleet Academy");
}
