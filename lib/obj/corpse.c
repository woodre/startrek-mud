/* /obj/corpse.c - Corpse left behind when a monster dies */

#include "/include/mudlib.h"

private string mob_name;
private int credits;
private int decay_time = 120;  // seconds until corpse vanishes

void create() {}

void setup(string name, int credit_value) {
    mob_name = name;
    credits = credit_value;
    call_out("decay", decay_time);
}

string query_short() {
    return "the corpse of " + mob_name;
}

int id(string s) {
    return strsrch(lower_case(s), "corpse") != -1 ||
           strsrch(lower_case(s), lower_case(mob_name)) != -1;
}

int move(mixed dest) {
    return move_object(this_object(), dest);
}

void examine(object viewer) {
    tell_object(viewer, "The lifeless body of " + mob_name + ".\n");
    if (credits > 0)
        tell_object(viewer, "You notice " + credits + " credits in a pouch.\n");
    // Show any dropped items in the corpse
    object ob = first_inventory(this_object());
    while (ob) {
        tell_object(viewer, "  " + ob->query_short() + " is inside.\n");
        ob = next_inventory(ob);
    }
}

int cmd_loot(string arg) {
    if (!credits && !first_inventory(this_object())) {
        write("The corpse is empty.\n");
        return 1;
    }
    if (credits > 0) {
        write("You loot " + credits + " credits from " + mob_name + ".\n");
        // TODO: add credits to player wallet
        credits = 0;
    }
    object ob = first_inventory(this_object());
    while (ob) {
        object next = next_inventory(ob);
        ob->move(environment(this_object()));
        write("You take " + ob->query_short() + " from the corpse.\n");
        ob = next;
    }
    return 1;
}

void init() {
    add_action("cmd_loot", "loot");
    add_action("cmd_loot", "search");
}

void decay() {
    if (environment(this_object()))
        tell_room(environment(this_object()),
            "The corpse of " + mob_name + " crumbles to dust.\n", ({ }));
    destruct(this_object());
}
