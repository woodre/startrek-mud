inherit "/std/room";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("Station Counselor's Office");
    set_long("A warmly lit, comfortable office with soft chairs and shelves of Betazoid artwork. The counselor's desk holds a single candle and a small vase of fresh flowers. The room seems designed to put you at ease - and you realize it is working.");
    set_exit("east", "/d/starfleet/rooms/main_deck");
    set_zone("Deep Space Nine");
}
