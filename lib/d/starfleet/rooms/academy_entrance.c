/* Starfleet Academy - Main Entrance */

inherit "/std/room";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("Starfleet Academy - Main Entrance");
    set_long(
        "You stand at the grand entrance to Starfleet Academy, San Francisco, Earth. " +
        "Twin columns of gleaming duranium flank the arching gateway, above which the " +
        "emblem of the United Federation of Planets glows in polished latinum. Behind " +
        "you, the bay shimmers under morning sunlight. Cadets in red and gold uniforms " +
        "hurry past, data padds in hand. A bulletin board near the gate lists orientation " +
        "schedules and mission assignments."
    );
    set_exit("north", "/d/starfleet/rooms/academy_quad");
    set_exit("south", "/d/starfleet/rooms/civilian_docking");
    set_exit("east",  "/d/starfleet/rooms/medical_bay");
    set_exit("west",  "/d/starfleet/rooms/commerce_deck");
    set_zone("Starfleet Academy");
}

void reset() {
    // Spawn a cadet NPC if none present
    object ob = first_inventory(this_object());
    int found = 0;
    while (ob) {
        if (!living(ob) || IS_PLAYER(ob)) { ob = next_inventory(ob); continue; }
        if (strsrch(ob->query_name(), "cadet") != -1) { found = 1; break; }
        ob = next_inventory(ob);
    }
    if (!found) {
        object cadet = clone_object("/d/starfleet/npcs/cadet");
        cadet->move(this_object());
    }
}
