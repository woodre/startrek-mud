/* /std/room.c
 * Base room object for Star Trek: Infinite Horizons
 */

#include "/include/mudlib.h"

private string short_desc;
private string long_desc;
private mapping exits;       // direction -> room path
private int light_level;     // 0=dark, 1=dim, 2=normal, 3=bright
private string room_type;    // "interior", "space", "planet", etc.
private string zone;         // zone name for grouping
private object *monsters;    // tracked monster references
private int reset_interval;  // seconds between resets

void create() {
    exits = ([ ]);
    light_level = 2;
    room_type = "interior";
    zone = "unknown";
    reset_interval = 300;
    monsters = ({ });
    call_out("room_reset", reset_interval);
}

// ============================================================
// DESCRIPTORS
// ============================================================
void set_short(string s)     { short_desc = s; }
void set_long(string s)      { long_desc = s; }
string query_short()         { return short_desc; }
string query_long()          { return long_desc; }
void set_light(int l)        { light_level = l; }
int  query_light()           { return light_level; }
void set_room_type(string t) { room_type = t; }
void set_zone(string z)      { zone = z; }

// ============================================================
// EXITS
// ============================================================
void set_exit(string dir, string dest) { exits[dir] = dest; }
void remove_exit(string dir)           { map_delete(exits, dir); }
string query_exit(string dir) {
    if (member(exits, dir)) return exits[dir];
    return 0;
}
mapping query_exits() { return copy(exits); }

// ============================================================
// LOOK
// ============================================================
void look(object viewer) {
    if (light_level == 0) {
        tell_object(viewer, "It is pitch dark here. You can't see a thing.\n");
        return;
    }
    // Room title
    tell_object(viewer, C_CYAN + short_desc + C_RESET + "\n");
    // Long desc with word wrap
    if (long_desc)
        tell_object(viewer, wrap_string(long_desc, 70) + "\n");
    tell_object(viewer, "\n");
    // Exits
    string *exit_dirs = m_indices(exits);
    if (sizeof(exit_dirs))
        tell_object(viewer, C_GREEN + "Exits: " + C_RESET +
                    implode(exit_dirs, ", ") + "\n");
    else
        tell_object(viewer, C_GREY + "[No exits]\n" + C_RESET);
    // Items and monsters in the room
    object ob = first_inventory(this_object());
    string things = "";
    while (ob) {
        if (living(ob) && ob != viewer)
            things += "  " + C_LRED + cap_str(ob->query_name()) + C_RESET + " is here.\n";
        else if (!living(ob))
            things += "  " + ob->query_short() + " is here.\n";
        ob = next_inventory(ob);
    }
    if (sizeof(things))
        tell_object(viewer, things);
}

// ============================================================
// INIT (called when a living enters the room)
// ============================================================
void init() {
    // Rooms can define custom commands here
}

// ============================================================
// RESET (called periodically to respawn items/monsters)
// ============================================================
void room_reset() {
    reset();
    call_out("room_reset", reset_interval);
}

void reset() {
    // Override in subclass to respawn monsters/items
}

// ============================================================
// EXAMINE (for specific objects/features in the room)
// ============================================================
void examine_feature(string feature, object viewer) {
    tell_object(viewer, "You see nothing special about the " + feature + ".\n");
}
