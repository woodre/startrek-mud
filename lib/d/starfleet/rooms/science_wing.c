/* Starfleet Academy - Science Wing */

inherit "/std/room";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("Starfleet Academy - Science Wing");
    set_long(
        "The Science Wing is a cathedral of knowledge, its high ceilings lost in " +
        "shadows above rows of glowing consoles and holoprojectors. Specimen jars " +
        "of alien flora line the shelves alongside star charts and xenobiology texts. " +
        "A massive LCARS display on the east wall shows the current stellar cartography " +
        "of the Alpha and Beta Quadrants. Science cadets debate the implications of " +
        "a recent subspace anomaly detected near the Badlands. The air smells faintly " +
        "of ozone and lubricant from nearby diagnostic equipment."
    );
    set_exit("east",  "/d/starfleet/rooms/academy_quad");
    set_exit("north", "/d/starfleet/rooms/vulcan_embassy");
    set_zone("Starfleet Academy");
}

void reset() {
    object ob = first_inventory(this_object());
    int found = 0;
    while (ob) {
        if (!IS_PLAYER(ob) && living(ob) && strsrch(ob->query_name(), "science") != -1)
            { found = 1; break; }
        ob = next_inventory(ob);
    }
    if (!found) {
        object sci = clone_object("/d/starfleet/npcs/science_cadet");
        sci->move(this_object());
    }
}
