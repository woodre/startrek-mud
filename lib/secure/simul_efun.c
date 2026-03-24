/* /secure/simul_efun.c
 * Simulated efuns - globally available to all objects
 * LDMud 3.6.x compatible
 */

void create() {
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
    if (!s || !strlen(s)) return s;
    string result = "";
    string *words = explode(s, " ");
    int col = 0;
    int i;
    for (i = 0; i < sizeof(words); i++) {
        string word = words[i];
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

// strsrch compatibility: find needle in haystack, return pos or -1
// LDMud 3.6 uses strstr() as an efun; this sfun wraps it for our code
int strsrch(string haystack, string needle) {
    if (!haystack || !needle) return -1;
    return strstr(haystack, needle, 0);
}

/* ============================================================
 * NUMBER UTILITIES
 * ============================================================ */

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

// Find a player by name (prefix match)
object find_player(string name) {
    object *obs = users();
    int i;
    string lname = lower_case(name);
    for (i = 0; i < sizeof(obs); i++) {
        object ob = obs[i];
        if (ob->is_player() &&
            strstr(lower_case(ob->query_name()), lname, 0) == 0)
            return ob;
    }
    return 0;
}

// Find a living object in a room by id string
object find_living_in_room(string name, object room) {
    if (!room) return 0;
    object ob = first_inventory(room);
    while (ob) {
        if (living(ob) && ob->id(name))
            return ob;
        ob = next_inventory(ob);
    }
    return 0;
}

// Tell all players in a room, optionally excluding some
void tell_room(object room, string msg, object *exclude) {
    if (!room) return;
    object ob = first_inventory(room);
    while (ob) {
        if (interactive(ob) && member(exclude, ob) == -1)
            tell_object(ob, msg);
        ob = next_inventory(ob);
    }
}

/* ============================================================
 * COMBAT / STAT UTILITIES
 * ============================================================ */

// XP required to reach a level
int xp_for_level(int level) {
    // Simple exponential: 100 * 1.5^(level-1)
    int xp = 100;
    int i;
    for (i = 1; i < level; i++)
        xp = (xp * 3) / 2;
    return xp;
}

// Random number between min and max inclusive
int rng(int min_val, int max_val) {
    if (min_val >= max_val) return min_val;
    return min_val + random(max_val - min_val + 1);
}

// ANSI health bar string
string health_bar(int current, int maximum, int width) {
    if (maximum <= 0) return repeat_string("-", width);
    int filled = (current * width) / maximum;
    if (filled < 0) filled = 0;
    if (filled > width) filled = width;
    int pct = percent(current, maximum);
    string color;
    if (pct >= 75)      color = "\033[32m";   // green
    else if (pct >= 40) color = "\033[33m";   // yellow
    else                color = "\033[31m";   // red
    return color + repeat_string("=", filled) +
           "\033[90m" + repeat_string("-", width - filled) + "\033[0m";
}

// Quality-colored item name
string quality_name(int quality, string name) {
    string color;
    switch(quality) {
        case 0:  color = "\033[90m"; break;   // grey  - poor
        case 1:  color = "\033[37m"; break;   // white - common
        case 2:  color = "\033[32m"; break;   // green - uncommon
        case 3:  color = "\033[36m"; break;   // cyan  - rare
        case 4:  color = "\033[35m"; break;   // magenta - epic
        default: color = "\033[38;5;214m";    // orange - legendary
    }
    return color + name + "\033[0m";
}

/* ============================================================
 * MESSAGE FORMATTING
 * ============================================================ */

void notify_room(string msg, object actor) {
    if (!environment(actor)) return;
    tell_room(environment(actor), msg, ({ actor }));
}
