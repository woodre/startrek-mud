inherit "/std/room";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("Trill Symbiosis Commission Office");
    set_long("A quiet ward maintained by the Trill Symbiosis Commission. Medical monitors track joined Trill crew members. Tanks of symbionts float in a preservation solution behind glass. The weight of centuries of memory is palpable.");
    set_exit("south", "/d/starfleet/rooms/main_deck");
    set_zone("Deep Space Nine");
}
