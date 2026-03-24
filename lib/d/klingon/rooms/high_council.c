inherit "/std/room";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("Great Hall - High Council Chamber");
    set_long("The Great Hall of the Klingon High Council is an imposing space of stone and shadow. The long council table dominates the center. Torches in iron sconces cast moving shadows across banners of Klingon noble Houses. The Chancellor's throne is empty. A mood of uneasy power pervades.");
    set_exit("south", "/d/klingon/rooms/warrior_hall");
    set_zone("Klingon Empire");
}
