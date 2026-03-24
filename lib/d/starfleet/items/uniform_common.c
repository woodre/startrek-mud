/* Starfleet Standard Uniform - Common quality chest armor */

inherit "/std/armor";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("a standard Starfleet uniform");
    set_long("A standard Starfleet uniform in the classic division colors. Lightweight " +
             "and comfortable, the uniform incorporates basic trauma-dispersal weave " +
             "that provides minimal but real protection. The combadge gleams on the chest.");
    add_id("uniform"); add_id("starfleet uniform"); add_id("standard uniform");
    set_quality(QUALITY_COMMON);
    set_armor_type(ATYPE_UNIFORM);
    set_equip_slot(SLOT_CHEST);
    set_armor_value(15);
    set_value(80);
    set_stat_bonus(STAT_SPIRIT, 3);
}
