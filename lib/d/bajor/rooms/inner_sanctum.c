inherit "/std/room";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("Temple of the Prophets - Inner Sanctum");
    set_long("The inner sanctum is a place of profound silence. Light streams through crystal panels in the domed ceiling, casting geometric patterns on the stone floor. The Orb of Prophecy and Change stands in an alcove, its case slightly ajar. Looking upon it, you feel a strange pull - as if the Prophets themselves are aware of your presence.");
    set_exit("south", "/d/bajor/rooms/temple_entrance");
    set_zone("Bajor");
}
