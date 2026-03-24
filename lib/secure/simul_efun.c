/* /secure/simul_efun.c
 * Simulated efuns - functions available globally to all objects
 * Star Trek: Infinite Horizons
 */

#include "/include/mudlib.h"

void create() {
    seteuid("root");
}

/* ============================================================
 * STRING UTILITIES
 * ============================================================ */

// Capitalize first letter
string cap_str(string s) {
    if (!s || !strlen(s)) return s;
    return upper_case(s[0..0]) + s[1..];
}

// Add article (a/an) before a string
string add_article(string s) {
    if (!s || !strlen(s)) return s;
    string first = lower_case(s[0..0]);
    if (first == "a" || first == "e" || first == "i" ||
        first == "o" || first == "u")
        return "an " + s;
    return "a " + s;
}

// Wrap long strings at column width
string wrap_string(string s, int width) {
    string result = "";
    string *words = explode(s, " ");
    int col = 0;
    foreach (string word : words) {
        int wlen = strlen(word);
        if (col + wlen + 1 > width && col > 0) {
            result += "\n";
            col = 0;
        }
        if (col > 0) { result += " "; col++; }
        result += word;
        col += wlen;
    }
    return result;
}

// Repeat a string N times
string repeat_string(string s, int n) {
    string result = "";
    int i;
    for (i = 0; i < n; i++)
        result += s;
    return result;
}

// Center a string in a given width
string center_string(string s, int width) {
    int len = strlen(s);
    if (len >= width) return s;
    int pad = (width - len) / 2;
    return repeat_string(" ", pad) + s + repeat_string(" ", width - len - pad);
}

/* ============================================================
 * NUMBER UTILITIES
 * ============================================================ */

// Integer to ordinal string (1st, 2nd, 3rd...)
string ordinal(int n) {
    switch(n % 10) {
        case 1: return (n % 100 == 11) ? n + "th" : n + "st";
        case 2: return (n % 100 == 12) ? n + "th" : n + "nd";
        case 3: return (n % 100 == 13) ? n + "th" : n + "rd";
        default: return n + "th";
    }
}

// Clamp value between min and max
int clamp(int val, int min_val, int max_val) {
    if (val < min_val) return min_val;
    if (val > max_val) return max_val;
    return val;
}

// Calculate percentage
int percent(int part, int total) {
    if (total == 0) return 0;
    return (part * 100) / total;
}

/* ============================================================
 * PLAYER UTILITIES
 * ============================================================ */

// Find a player by name (partial match)
object find_player(string name) {
    object *obs = users();
    foreach (object ob : obs) {
        if (IS_PLAYER(ob) && strsrch(lower_case(ob->query_name()), lower_case(name)) == 0)
            return ob;
    }
    return 0;
}

// Find living object in a room by name
object find_living_in_room(string name, object room) {
    object ob;
    ob = first_inventory(room);
    while (ob) {
        if (living(ob) && id(ob, name))
            return ob;
        ob = next_inventory(ob);
    }
    return 0;
}

// Tell all players in a room
void tell_room(object room, string msg, object *exclude) {
    object ob;
    ob = first_inventory(room);
    while (ob) {
        if (interactive(ob) && !member(exclude, ob))
            tell_object(ob, msg);
        ob = next_inventory(ob);
    }
}

/* ============================================================
 * COMBAT / STAT UTILITIES
 * ============================================================ */

// Calculate XP needed for a given level
int xp_for_level(int level) {
    return to_int(XP_BASE * pow(XP_MULTIPLIER, level - 1));
}

// Generate a random number between min and max (inclusive)
int rng(int min_val, int max_val) {
    if (min_val >= max_val) return min_val;
    return min_val + random(max_val - min_val + 1);
}

// Color-code a number as a health bar segment
string health_bar(int current, int maximum, int width) {
    if (maximum <= 0) return repeat_string("-", width);
    int filled = (current * width) / maximum;
    filled = clamp(filled, 0, width);
    int pct = percent(current, maximum);
    string color;
    if (pct >= 75) color = C_GREEN;
    else if (pct >= 40) color = C_YELLOW;
    else color = C_RED;
    return color + repeat_string("=", filled) + C_GREY +
           repeat_string("-", width - filled) + C_RESET;
}

// Quality-colored item name
string quality_name(int quality, string name) {
    return QUALITY_COLOR(quality) + name + C_RESET;
}

/* ============================================================
 * MESSAGE FORMATTING
 * ============================================================ */

// Notify all interactive users in a room except the actor
void notify_room(string msg, object actor) {
    if (!environment(actor)) return;
    tell_room(environment(actor), msg, ({ actor }));
}

// Send a formatted combat message to player
void combat_msg(object player, string msg) {
    tell_object(player, C_LRED + "[Combat] " + C_RESET + msg + "\n");
}

// Send a formatted system message
void sys_msg(object player, string msg) {
    tell_object(player, C_CYAN + "[System] " + C_RESET + msg + "\n");
}

// Send a formatted info message
void info_msg(object player, string msg) {
    tell_object(player, C_YELLOW + msg + C_RESET + "\n");
}
