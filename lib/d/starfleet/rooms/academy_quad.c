/* Starfleet Academy - Central Quad */

inherit "/std/room";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("Starfleet Academy - Central Quad");
    set_long(
        "The Academy quad is a sweeping open plaza of green grass and ancient oak trees. " +
        "Holographic training dummies flicker near the western edge, drawing sparring " +
        "cadets with phaser training weapons. At the center stands a proud statue of " +
        "Admiral Jonathan Archer flanked by an Earth Starfleet NX-class model encased " +
        "in transparent aluminum. Paths lead to the various academic buildings and the " +
        "dormitory complex to the north."
    );
    set_exit("south", "/d/starfleet/rooms/academy_entrance");
    set_exit("north", "/d/starfleet/rooms/dormitory");
    set_exit("east",  "/d/starfleet/rooms/tactical_wing");
    set_exit("west",  "/d/starfleet/rooms/science_wing");
    set_exit("up",    "/d/starfleet/rooms/observation_tower");
    set_zone("Starfleet Academy");
}

void reset() {
    // Spawn training drone
    object ob = first_inventory(this_object());
    int found = 0;
    while (ob) {
        if (!IS_PLAYER(ob) && living(ob) && strsrch(ob->query_name(), "drone") != -1)
            { found = 1; break; }
        ob = next_inventory(ob);
    }
    if (!found) {
        object drone = clone_object("/d/starfleet/npcs/training_drone");
        drone->move(this_object());
    }
}
