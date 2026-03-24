/* Klingon Empire - Warrior Hall (Klingon starting zone) */

inherit "/std/room";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("Qo'noS - Hall of Warriors");
    set_long(
        "The Hall of Warriors on Qo'noS reeks of bloodwine and honor. Massive stone " +
        "pillars carved with the battles of Kahless line the great hall. Mounted " +
        "trophies of defeated enemies from a dozen worlds cover the walls. The " +
        "fire pits burn with constant flame, casting everything in a red-orange glow. " +
        "Warriors sharpen their bat'leths and trade battle stories with boisterous " +
        "laughter. The High Council chambers lie to the north. The training grounds " +
        "are to the east, where the sounds of combat ring out endlessly. " +
        "Klingon warriors begin their path to glory here."
    );
    set_exit("north", "/d/klingon/rooms/high_council");
    set_exit("east",  "/d/klingon/rooms/training_grounds");
    set_exit("south", "/d/klingon/rooms/feast_hall");
    set_exit("west",  "/d/starfleet/rooms/main_deck");
    set_zone("Klingon Empire");
}

void reset() {
    object ob = first_inventory(this_object());
    int found = 0;
    while (ob) {
        if (!IS_PLAYER(ob) && living(ob)) { found = 1; break; }
        ob = next_inventory(ob);
    }
    if (!found) {
        object warrior = clone_object("/d/klingon/npcs/klingon_warrior");
        warrior->move(this_object());
    }
}
