inherit "/std/room";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("Starfleet Academy - Dormitory Block");
    set_long("Rows of compact but comfortable quarters for Academy cadets. Each room holds two bunks, a shared desk, and a small viewport. The halls smell of coffee and ambition.");
    set_exit("south", "/d/starfleet/rooms/academy_quad");
    set_zone("Starfleet Academy");
}
