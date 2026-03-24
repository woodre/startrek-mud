/* Klingon Training Grounds */

inherit "/std/room";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("Qo'noS - Klingon Training Grounds");
    set_long(
        "The Klingon training grounds are a brutal proving arena of packed earth and " +
        "blood-stained stone. Warriors clash with bat'leths, mek'leths, and bare fists " +
        "in savage practice bouts. The victors roar in triumph; the defeated pick " +
        "themselves up without complaint - weakness is not tolerated here. Weapon racks " +
        "hold training blades along the perimeter. A grizzled veteran warrior oversees " +
        "the exercises, offering terse corrections and occasional praise. Several " +
        "targ hides are stretched on frames - the beasts themselves prowl a pen nearby."
    );
    set_exit("west",  "/d/klingon/rooms/warrior_hall");
    set_exit("north", "/d/klingon/rooms/armory");
    set_zone("Klingon Empire");
}

void reset() {
    object ob = first_inventory(this_object());
    int count = 0;
    while (ob) {
        if (!IS_PLAYER(ob) && living(ob)) count++;
        ob = next_inventory(ob);
    }
    if (count < 2) {
        object targ = clone_object("/d/klingon/npcs/battle_targ");
        targ->move(this_object());
        object warrior = clone_object("/d/klingon/npcs/klingon_warrior");
        warrior->move(this_object());
    }
}
