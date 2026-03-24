inherit "/std/room";
#include "/include/mudlib.h"
void create() {
    ::create();
    set_short("Bajoran Village - Ashalla Outskirts");
    set_long("A quiet Bajoran village at the edge of the capital Ashalla. Stone and timber homes line the road. Bajoran citizens go about their lives with a resilience earned through decades of occupation and now freedom. Children play near the communal spring. The smell of Bajoran spices drifts from a nearby bakery.");
    set_exit("north", "/d/bajor/rooms/temple_entrance");
    set_zone("Bajor");
}
void reset() {
    // Spawn a lurking Cardassian spy at low chance
    if (random(3) == 0) {
        object ob = first_inventory(this_object());
        int found = 0;
        while (ob) {
            if (!IS_PLAYER(ob) && living(ob) && strsrch(ob->query_name(), "cardassian") != -1)
                { found = 1; break; }
            ob = next_inventory(ob);
        }
        if (!found) {
            object spy = clone_object("/d/bajor/npcs/cardassian_spy");
            spy->move(this_object());
        }
    }
}
