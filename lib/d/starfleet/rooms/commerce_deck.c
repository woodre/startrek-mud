/* Commerce Deck - Vendor area */

inherit "/std/room";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("Deep Space Nine - Commerce Deck");
    set_long(
        "The Commerce Deck caters to every need - for a price. Ferengi vendors compete " +
        "for attention with holographic advertisements and shouted deals. A weapons " +
        "merchant displays phasers and disruptors behind transparent aluminum cases. " +
        "An armor vendor nearby offers Starfleet-certified body armor ranging from " +
        "standard issue to custom tactical rigs. The smell of Jumja sticks and fresh " +
        "raktajino fills the air. The famous Rule of Acquisition #1 - 'Once you have " +
        "their money, never give it back' - is painted above the entrance."
    );
    set_exit("east",  "/d/starfleet/rooms/academy_entrance");
    set_exit("north", "/d/starfleet/rooms/main_deck");
    set_zone("Deep Space Nine");
}

void reset() {
    object ob = first_inventory(this_object());
    int found_vendor = 0;
    while (ob) {
        if (!IS_PLAYER(ob) && living(ob) && strsrch(ob->query_name(), "merchant") != -1)
            { found_vendor = 1; break; }
        ob = next_inventory(ob);
    }
    if (!found_vendor) {
        object merchant = clone_object("/d/starfleet/npcs/ferengi_merchant");
        merchant->move(this_object());
    }
}
