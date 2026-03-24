inherit "/std/room";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("Klingon Feast Hall");
    set_long("Long tables overflow with gagh, rokeg blood pie, and rivers of warnog and bloodwine. Warriors eat, argue, sing battle songs, and settle minor disputes with fists. A victory feast is always either imminent or ongoing. The noise is staggering.");
    set_exit("north", "/d/klingon/rooms/warrior_hall");
    set_zone("Klingon Empire");
}
