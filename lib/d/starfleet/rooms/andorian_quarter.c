inherit "/std/room";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("Andorian Quarter");
    set_long("The Andorian section is kept cold and blue-lit, the temperature enough to make a Human's breath mist. Andorian tapestries of battle scenes cover the walls. The antennae of Andorian occupants swivel toward any newcomer with instinctive alertness.");
    set_exit("east", "/d/starfleet/rooms/main_deck");
    set_zone("Deep Space Nine");
}
