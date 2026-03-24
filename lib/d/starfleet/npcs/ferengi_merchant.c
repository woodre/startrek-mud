/* Ferengi Merchant - Sells gear */

inherit "/std/monster";

#include "/include/mudlib.h"

private mapping shop_inventory;

void create() {
    ::create();
    set_short("Grul the Ferengi merchant");
    set_long("A grinning Ferengi merchant stands behind a cluttered display case, " +
             "his enormous ears perked at the sound of approaching footsteps - or " +
             "perhaps latinum. His teeth glitter as he sizes up every passerby for " +
             "profit potential. His vest is covered in tiny latinum clasps.");
    add_id("ferengi");
    add_id("merchant");
    add_id("grul");
    add_id("vendor");
    set_level(5);
    set_stat(STAT_PRESENCE, 20);
    set_stat(STAT_AGILITY, 14);
    recalculate_derived_stats();
    set_hp(query_max_hp());
    set_xp_value(0);
    set_credits_value(0);
    set_faction("neutral");
    set_aggro(0);
    // Stock the shop
    shop_inventory = ([
        "Type-1 Phaser":        ([ "path": "/d/starfleet/items/type1_phaser", "price": 50 ]),
        "Type-2 Phaser":        ([ "path": "/d/starfleet/items/type2_phaser", "price": 150 ]),
        "Starfleet Uniform":    ([ "path": "/d/starfleet/items/uniform_common","price": 80 ]),
        "Combat Vest":          ([ "path": "/d/starfleet/items/combat_vest",   "price": 200 ]),
    ]);
}

void init() {
    ::init();
    add_action("cmd_list",  "list");
    add_action("cmd_buy",   "buy");
    add_action("cmd_sell",  "sell");
}

int cmd_list(string arg) {
    tell_object(this_player(), "Grul rubs his hands together. \"Today's inventory, " +
                "at very reasonable prices!\"\n");
    tell_object(this_player(), C_YELLOW + repeat_string("-", 50) + C_RESET + "\n");
    tell_object(this_player(), sprintf("  %-25s %s\n", "Item", "Price"));
    tell_object(this_player(), C_YELLOW + repeat_string("-", 50) + C_RESET + "\n");
    string *items = m_indices(shop_inventory);
    foreach (string iname : items) {
        int price = shop_inventory[iname]["price"];
        tell_object(this_player(), sprintf("  %-25s %d credits\n", iname, price));
    }
    tell_object(this_player(), C_YELLOW + repeat_string("-", 50) + C_RESET + "\n");
    return 1;
}

int cmd_buy(string arg) {
    if (!arg) { write("Buy what? (type 'list' to see inventory)\n"); return 1; }
    string *items = m_indices(shop_inventory);
    string found_key = 0;
    foreach (string k : items) {
        if (strsrch(lower_case(k), lower_case(arg)) != -1) {
            found_key = k;
            break;
        }
    }
    if (!found_key) {
        write("Grul shrugs. \"I don't carry that. Perhaps you misread the inventory?\"\n");
        return 1;
    }
    int price = shop_inventory[found_key]["price"];
    // TODO: Check player credits
    object item = clone_object(shop_inventory[found_key]["path"]);
    item->move(this_player());
    write("Grul smiles. \"Excellent choice! That'll be " + price + " credits. Pleasure doing business!\"\n");
    write("You receive: " + quality_name(item->query_quality(), item->query_short()) + "\n");
    return 1;
}

int cmd_sell(string arg) {
    write("Grul waves a hand. \"I'm buying! Bring me your unwanted items.\"\n");
    return 1;
}
