/* Klingon Warrior Armor - Uncommon heavy chest */

inherit "/std/armor";

#include "/include/mudlib.h"

void create() {
    ::create();
    set_short("Klingon warrior armor");
    set_long("Heavy Klingon warrior armor forged from tritanium-alloy plates, each one " +
             "engraved with the House glyph of the wearer's lineage. The shoulder pauldrons " +
             "are spiked. The chest plate bears deep gouges from previous battles - " +
             "each one a story of survival.");
    add_id("warrior armor"); add_id("klingon armor"); add_id("armor");
    set_quality(QUALITY_UNCOMMON);
    set_armor_type(ATYPE_HEAVY);
    set_equip_slot(SLOT_CHEST);
    set_armor_value(65);
    set_value(350);
    set_stat_bonus(STAT_STAMINA, 8);
    set_stat_bonus(STAT_STRENGTH, 6);
}
