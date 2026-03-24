inherit "/std/room";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("Klingon Imperial Armory");
    set_long("Rack upon rack of bladed weapons line the walls - bat'leths, mek'leths, d'k tahgs, and weapons with no Federation equivalent. An armorer carefully oils a bat'leth with practiced strokes. The smell of metal and weapon oil fills the room.");
    set_exit("south", "/d/klingon/rooms/training_grounds");
    set_zone("Klingon Empire");
}
void reset() {
    object ob = first_inventory(this_object());
    int found = 0;
    while (ob) {
        if (!living(ob) && ob->id("bat'leth")) { found = 1; break; }
        ob = next_inventory(ob);
    }
    if (!found) {
        object bat = clone_object("/d/klingon/items/batlet");
        bat->move(this_object());
    }
}
