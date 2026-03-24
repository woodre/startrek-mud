/* Targ Hide - Crafting material / vendor trash */

inherit "/std/item";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("a targ hide");
    set_long("The rough, bristled hide of a battle targ. Klingons use these for leather working and making weapon grips.");
    add_id("targ hide"); add_id("hide");
    set_quality(QUALITY_POOR);
    set_item_type(ITYPE_MISC);
    set_value(5);
    set_weight(500);
}
