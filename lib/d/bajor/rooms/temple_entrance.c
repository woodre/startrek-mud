/* Bajor - Temple of the Prophets */

inherit "/std/room";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("Bajor - Temple of the Prophets");
    set_long(
        "The ancient Temple of the Prophets stands at the heart of Bajoran spiritual " +
        "life. Ornate stone arches frame the entrance, carved with images of the " +
        "Tears of the Prophets - the sacred Orbs. Bajoran monks in flowing robes " +
        "move silently through the incense-scented corridors. Candles cast warm " +
        "light across the mosaic floor that depicts the Celestial Temple. A pedestal " +
        "near the entrance holds an Orb case, its contents a soft, shifting glow. " +
        "Even non-Bajorans feel a strange sense of calm in this place. Beyond the " +
        "northern arch lies the inner sanctum, while the outer grounds spread to the south."
    );
    set_exit("north", "/d/bajor/rooms/inner_sanctum");
    set_exit("south", "/d/bajor/rooms/bajoran_village");
    set_exit("up",    "/d/starfleet/rooms/main_deck");
    set_zone("Bajor");
}

void reset() {
    object ob = first_inventory(this_object());
    int found = 0;
    while (ob) {
        if (!IS_PLAYER(ob) && living(ob)) { found = 1; break; }
        ob = next_inventory(ob);
    }
    if (!found) {
        object monk = clone_object("/d/bajor/npcs/bajoran_monk");
        monk->move(this_object());
    }
}
