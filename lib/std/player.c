/* /std/player.c
 * Player object - inherits living.c
 * Handles persistence, commands, character creation
 */

inherit "/std/living";

#include "/include/mudlib.h"
#include "/include/races.h"

private string password;
private string title;
private string description;
private int creation_complete;
private int creation_step;
private string pending_race;
private string pending_class;
private mapping known_commands;
private int total_kills;
private int total_deaths;
private string *inventory_bag;  // non-equipped carried items tracked by file_name

void create() {
    ::create();
    title = "the Recruit";
    description = "A member of Starfleet.";
    creation_complete = 0;
    creation_step = 0;
    total_kills = 0;
    total_deaths = 0;
    known_commands = ([ ]);
    // set_living_name is called automatically when name is set in native mode
    call_out("regen_tick", 6);
}

int is_player() { return 1; }

// ============================================================
// PERSISTENCE
// ============================================================
void save_player() {
    save_object(PLAYER_SAVE_DIR + lower_case(query_name()));
}

int load_player(string pass) {
    if (!restore_object(PLAYER_SAVE_DIR + lower_case(query_name())))
        return 0;
    if (crypt(pass, password) != password)
        return 0;
    return 1;
}

void set_password(string pw) { password = pw; }
string query_password()      { return password; }

// ============================================================
// CHARACTER CREATION
// ============================================================
void start_creation() {
    creation_complete = 0;
    creation_step = 1;
    show_race_selection();
}

void show_race_selection() {
    write("\n" + C_CYAN + repeat_string("=", 60) + C_RESET + "\n");
    write(C_LYELLOW + center_string("CHOOSE YOUR RACE", 60) + C_RESET + "\n");
    write(C_CYAN + repeat_string("=", 60) + C_RESET + "\n\n");
    write(C_LGREEN + " 1" + C_RESET + ". Human       - " + C_WHITE + "Adaptable generalists. Bonus to Presence.\n" + C_RESET);
    write(C_LGREEN + " 2" + C_RESET + ". Vulcan       - " + C_WHITE + "Logical and strong. Bonus Intellect & Strength.\n" + C_RESET);
    write(C_LGREEN + " 3" + C_RESET + ". Klingon      - " + C_WHITE + "Fierce warriors. High Strength & Stamina.\n" + C_RESET);
    write(C_LGREEN + " 4" + C_RESET + ". Betazoid     - " + C_WHITE + "Empathic counselors. High Intellect & Spirit.\n" + C_RESET);
    write(C_LGREEN + " 5" + C_RESET + ". Andorian     - " + C_WHITE + "Aggressive fighters. High Agility & Strength.\n" + C_RESET);
    write(C_LGREEN + " 6" + C_RESET + ". Bajoran      - " + C_WHITE + "Resilient survivors. Bonus Spirit & Presence.\n" + C_RESET);
    write(C_LGREEN + " 7" + C_RESET + ". Ferengi      - " + C_WHITE + "Cunning traders. High Presence & Agility.\n" + C_RESET);
    write(C_LGREEN + " 8" + C_RESET + ". Trill        - " + C_WHITE + "Joined wisdom. High Intellect & Spirit.\n" + C_RESET);
    write(C_LGREEN + " 9" + C_RESET + ". Cardassian   - " + C_WHITE + "Disciplined soldiers. Bonus Stamina & Intellect.\n" + C_RESET);
    write(C_LGREEN + "10" + C_RESET + ". Bolian       - " + C_WHITE + "Social and adaptable. Bonus Presence & Agility.\n" + C_RESET);
    write("\n" + C_YELLOW + "Enter the number of your race: " + C_RESET);
    input_to("get_race_choice");
}

void get_race_choice(string str) {
    int choice = to_int(str);
    string *races = ALL_RACES;
    if (choice < 1 || choice > sizeof(races)) {
        write(C_RED + "Invalid choice. Enter a number 1-10.\n" + C_RESET);
        write("Enter the number of your race: ");
        input_to("get_race_choice");
        return;
    }
    pending_race = races[choice - 1];
    show_race_details(pending_race);
}

void show_race_details(string r) {
    mapping info = get_race_info(r);
    write("\n" + QUALITY_COLOR(3) + "--- " + cap_str(r) + " ---" + C_RESET + "\n");
    write(info["description"] + "\n\n");
    write(C_LGREEN + "Racial Bonuses:\n" + C_RESET);
    mapping bonuses = info["stat_bonuses"];
    string *skeys = m_indices(bonuses);
    foreach (string s : skeys)
        write("  " + cap_str(s) + ": +" + bonuses[s] + "\n");
    write("\n" + C_LGREEN + "Racial Ability: " + C_WHITE + info["ability_name"] + C_RESET + "\n");
    write("  " + info["ability_desc"] + "\n");
    write("\n[" + C_LGREEN + "Y" + C_RESET + "]es to confirm, [" + C_RED + "N" + C_RESET + "]o to go back: ");
    input_to("confirm_race");
}

void confirm_race(string str) {
    if (lower_case(str) == "y" || lower_case(str) == "yes") {
        set_race(pending_race);
        apply_race_stats(pending_race);
        show_class_selection();
    } else {
        show_race_selection();
    }
}

void show_class_selection() {
    write("\n" + C_CYAN + repeat_string("=", 60) + C_RESET + "\n");
    write(C_LYELLOW + center_string("CHOOSE YOUR DIVISION", 60) + C_RESET + "\n");
    write(C_CYAN + repeat_string("=", 60) + C_RESET + "\n\n");
    write(C_LRED   + "1. Tactical    " + C_RESET + "- Frontline combat. High damage and defense.\n");
    write(C_LBLUE  + "2. Science     " + C_RESET + "- Medicine and energy weapons. Healing focus.\n");
    write(C_LYELLOW+ "3. Engineering " + C_RESET + "- Support and fortification. Tanking and buffs.\n");
    write(C_LGREEN + "4. Operations  " + C_RESET + "- Versatile multi-role. Adapts to any situation.\n");
    write(C_LMAGENTA+"5. Command    " + C_RESET + "- Leadership auras. Buffs allies, directs battle.\n");
    write("\n" + C_YELLOW + "Enter your division [1-5]: " + C_RESET);
    input_to("get_class_choice");
}

void get_class_choice(string str) {
    int choice = to_int(str);
    string *classes = ALL_CLASSES;
    if (choice < 1 || choice > sizeof(classes)) {
        write(C_RED + "Invalid choice. Enter 1-5.\n" + C_RESET);
        write("Enter your division [1-5]: ");
        input_to("get_class_choice");
        return;
    }
    pending_class = classes[choice - 1];
    show_class_details(pending_class);
}

void show_class_details(string c) {
    mapping info = get_class_info(c);
    write("\n" + C_LCYAN + "--- " + cap_str(c) + " Division ---" + C_RESET + "\n");
    write(info["description"] + "\n\n");
    write(C_LGREEN + "Primary Stats: " + C_WHITE + info["primary_stat"] + C_RESET + "\n");
    write(C_LGREEN + "Armor: " + C_WHITE + info["armor_type"] + C_RESET + "\n");
    write(C_LGREEN + "Role: " + C_WHITE + info["role"] + C_RESET + "\n\n");
    write("[" + C_LGREEN + "Y" + C_RESET + "]es, [" + C_RED + "N" + C_RESET + "]o: ");
    input_to("confirm_class");
}

void confirm_class(string str) {
    if (lower_case(str) == "y" || lower_case(str) == "yes") {
        set_class(pending_class);
        apply_class_stats(pending_class);
        finalize_creation();
    } else {
        show_class_selection();
    }
}

void finalize_creation() {
    creation_complete = 1;
    write("\n" + C_LYELLOW + repeat_string("*", 60) + C_RESET + "\n");
    write(C_LYELLOW + center_string("CHARACTER CREATED", 60) + C_RESET + "\n");
    write(C_LYELLOW + repeat_string("*", 60) + C_RESET + "\n\n");
    write("Welcome to Star Trek: Infinite Horizons, " + C_LGREEN + query_name() + C_RESET + "!\n");
    write("Race: " + C_CYAN + cap_str(query_race()) + C_RESET +
          "   Division: " + C_CYAN + cap_str(query_class()) + C_RESET + "\n\n");
    save_player();
    setup_after_login();
}

// ============================================================
// POST-LOGIN SETUP
// ============================================================
void setup_after_login() {
    if (!creation_complete) {
        start_creation();
        return;
    }
    // Move to starting zone
    string start_room = "/d/starfleet/rooms/main_deck";
    switch(query_race()) {
        case RACE_KLINGON:   start_room = START_ZONE_KLINGON;   break;
        case RACE_BAJORAN:   start_room = START_ZONE_BAJORAN;   break;
        default: start_room = START_ZONE_HUMAN; break;
    }
    move(start_room);
    do_look();
    // Show MOTD
    write("\n");
    string motd = read_file(MOTD_FILE);
    if (motd) write(motd);
    write("\n");
}

void do_look() {
    object env = environment(this_object());
    if (!env) return;
    env->look(this_object());
}

// ============================================================
// RACE/CLASS SETUP
// ============================================================
mapping get_race_info(string r) {
    switch(r) {
        case RACE_HUMAN:
            return ([
                "description": "Humans are among the most adaptable and resourceful species in the galaxy. Their diplomatic skill and perseverance have made them natural leaders of the United Federation of Planets.",
                "stat_bonuses": ([ STAT_PRESENCE: 5, STAT_SPIRIT: 3 ]),
                "ability_name": "Fortitude",
                "ability_desc": "Draw on inner strength to regain 10% of max HP over 8 seconds (2 min cooldown)."
            ]);
        case RACE_VULCAN:
            return ([
                "description": "Vulcans are a highly logical species with remarkable mental and physical discipline. Their mastery of the mind meld and nerve pinch makes them formidable opponents.",
                "stat_bonuses": ([ STAT_INTELLECT: 8, STAT_STRENGTH: 5 ]),
                "ability_name": "Nerve Pinch",
                "ability_desc": "Incapacitate a humanoid target for 6 seconds (3 min cooldown)."
            ]);
        case RACE_KLINGON:
            return ([
                "description": "Klingons are a proud warrior race for whom honor in battle is paramount. Their physical superiority and battle fury make them devastating combatants.",
                "stat_bonuses": ([ STAT_STRENGTH: 10, STAT_STAMINA: 7, STAT_AGILITY: 3 ]),
                "ability_name": "Battle Fury",
                "ability_desc": "Enter a combat frenzy for 15 seconds, increasing all damage by 25% (5 min cooldown)."
            ]);
        case RACE_BETAZOID:
            return ([
                "description": "Betazoids are a fully telepathic humanoid species. Their empathic abilities allow them to sense the emotions and intentions of others, making them exceptional healers and counselors.",
                "stat_bonuses": ([ STAT_INTELLECT: 8, STAT_SPIRIT: 7 ]),
                "ability_name": "Empathic Scan",
                "ability_desc": "Sense the weaknesses of a target, revealing its stats and current HP (no cooldown)."
            ]);
        case RACE_ANDORIAN:
            return ([
                "description": "Andorians are an aggressive, militaristic people known for their blue skin and white hair. Their twin antennae grant them heightened awareness in combat.",
                "stat_bonuses": ([ STAT_AGILITY: 8, STAT_STRENGTH: 6 ]),
                "ability_name": "Antennae Awareness",
                "ability_desc": "Cannot be surprised or flanked; +10% dodge chance for 10 seconds in combat."
            ]);
        case RACE_BAJORAN:
            return ([
                "description": "Bajorans are a deeply spiritual people who survived the brutal Cardassian occupation through faith and resilience. Their connection to the Prophets grants them unusual endurance.",
                "stat_bonuses": ([ STAT_SPIRIT: 8, STAT_PRESENCE: 5 ]),
                "ability_name": "Prophet's Blessing",
                "ability_desc": "Receive a blessing that increases healing received by 15% for 30 seconds (4 min cooldown)."
            ]);
        case RACE_FERENGI:
            return ([
                "description": "Ferengi are cunning traders and opportunists. Their highly attuned hearing and love of profit give them advantages in negotiation and ambush tactics.",
                "stat_bonuses": ([ STAT_PRESENCE: 10, STAT_AGILITY: 5 ]),
                "ability_name": "Rule of Acquisition",
                "ability_desc": "Negotiate a discount with vendors, reducing item costs by 20% permanently."
            ]);
        case RACE_TRILL:
            return ([
                "description": "Trill can be joined with a symbiont that carries centuries of memories and experience. This accumulated wisdom grants them unparalleled insight.",
                "stat_bonuses": ([ STAT_INTELLECT: 7, STAT_SPIRIT: 6 ]),
                "ability_name": "Symbiont Knowledge",
                "ability_desc": "Access past host memories to gain +20% XP from all sources for 1 hour (24h cooldown)."
            ]);
        case RACE_CARDASSIAN:
            return ([
                "description": "Cardassians are a disciplined, militaristic species with exceptional memory and tactical minds. Their natural body armor and cold logic make them efficient soldiers.",
                "stat_bonuses": ([ STAT_STAMINA: 8, STAT_INTELLECT: 5 ]),
                "ability_name": "Photographic Memory",
                "ability_desc": "Recall any enemy's attack pattern; reduce damage taken from that enemy by 10% for the encounter."
            ]);
        case RACE_BOLIAN:
            return ([
                "description": "Bolians are sociable, blue-skinned humanoids known for their divided cartilage and exceptional social skills. They make natural diplomats and team players.",
                "stat_bonuses": ([ STAT_PRESENCE: 7, STAT_AGILITY: 5 ]),
                "ability_name": "Group Motivation",
                "ability_desc": "Inspire nearby allies, granting +5% to all stats for 20 seconds (3 min cooldown)."
            ]);
        default:
            return ([ "description": "Unknown race.", "stat_bonuses": ([ ]),
                      "ability_name": "None", "ability_desc": "None" ]);
    }
}

void apply_race_stats(string r) {
    mapping info = get_race_info(r);
    mapping bonuses = info["stat_bonuses"];
    string *keys = m_indices(bonuses);
    foreach (string s : keys)
        set_stat(s, query_base_stat(s) + bonuses[s]);
}

mapping get_class_info(string c) {
    switch(c) {
        case CLASS_TACTICAL:
            return ([
                "description": "Tactical officers are trained for combat operations. Whether serving as security, ground troops, or ship weapons officers, they excel at dealing and absorbing damage.",
                "primary_stat": "Strength, Agility",
                "armor_type":   "Medium or Heavy",
                "role":         "DPS / Tank"
            ]);
        case CLASS_SCIENCE:
            return ([
                "description": "Science officers combine medical knowledge with energy-based abilities. They keep their team alive through healing and weaken enemies with psionic and technological attacks.",
                "primary_stat": "Intellect, Spirit",
                "armor_type":   "Light (Uniform)",
                "role":         "Healer / Caster DPS"
            ]);
        case CLASS_ENGINEERING:
            return ([
                "description": "Engineers understand the systems that power a ship and can apply that knowledge in the field. They use fortification techniques, shield buffs, and heavy equipment.",
                "primary_stat": "Stamina, Intellect",
                "armor_type":   "Medium",
                "role":         "Tank / Support"
            ]);
        case CLASS_OPERATIONS:
            return ([
                "description": "Operations officers are masters of logistics and multi-tasking. They can fill any role on the fly, making them unpredictable and versatile.",
                "primary_stat": "Agility, Presence",
                "armor_type":   "Light or Medium",
                "role":         "Hybrid DPS / Support"
            ]);
        case CLASS_COMMAND:
            return ([
                "description": "Command officers lead from the front. Their presence boosts the effectiveness of allies and their tactical orders can turn the tide of any engagement.",
                "primary_stat": "Presence, Strength",
                "armor_type":   "Medium",
                "role":         "Buffer / Leader"
            ]);
        default:
            return ([ "description": "Unknown class.", "primary_stat": "", "armor_type": "", "role": "" ]);
    }
}

void apply_class_stats(string c) {
    switch(c) {
        case CLASS_TACTICAL:
            set_stat(STAT_STRENGTH, query_base_stat(STAT_STRENGTH) + 8);
            set_stat(STAT_AGILITY, query_base_stat(STAT_AGILITY) + 6);
            set_stat(STAT_STAMINA, query_base_stat(STAT_STAMINA) + 5);
            break;
        case CLASS_SCIENCE:
            set_stat(STAT_INTELLECT, query_base_stat(STAT_INTELLECT) + 10);
            set_stat(STAT_SPIRIT, query_base_stat(STAT_SPIRIT) + 7);
            break;
        case CLASS_ENGINEERING:
            set_stat(STAT_STAMINA, query_base_stat(STAT_STAMINA) + 10);
            set_stat(STAT_INTELLECT, query_base_stat(STAT_INTELLECT) + 5);
            set_stat(STAT_STRENGTH, query_base_stat(STAT_STRENGTH) + 3);
            break;
        case CLASS_OPERATIONS:
            set_stat(STAT_AGILITY, query_base_stat(STAT_AGILITY) + 8);
            set_stat(STAT_PRESENCE, query_base_stat(STAT_PRESENCE) + 5);
            set_stat(STAT_SPIRIT, query_base_stat(STAT_SPIRIT) + 3);
            break;
        case CLASS_COMMAND:
            set_stat(STAT_PRESENCE, query_base_stat(STAT_PRESENCE) + 10);
            set_stat(STAT_STRENGTH, query_base_stat(STAT_STRENGTH) + 5);
            set_stat(STAT_STAMINA, query_base_stat(STAT_STAMINA) + 3);
            break;
    }
    recalculate_derived_stats();
}

// ============================================================
// COMMAND INIT
// ============================================================
void init() {
    // Add player commands
    add_action("cmd_look",    "look");
    add_action("cmd_look",    "l");
    add_action("cmd_north",   "north");
    add_action("cmd_north",   "n");
    add_action("cmd_south",   "south");
    add_action("cmd_south",   "s");
    add_action("cmd_east",    "east");
    add_action("cmd_east",    "e");
    add_action("cmd_west",    "west");
    add_action("cmd_west",    "w");
    add_action("cmd_up",      "up");
    add_action("cmd_up",      "u");
    add_action("cmd_down",    "down");
    add_action("cmd_down",    "d");
    add_action("cmd_say",     "say");
    add_action("cmd_say",     "'");
    add_action("cmd_tell",    "tell");
    add_action("cmd_who",     "who");
    add_action("cmd_score",   "score");
    add_action("cmd_score",   "sc");
    add_action("cmd_stats",   "stats");
    add_action("cmd_inv",     "inventory");
    add_action("cmd_inv",     "inv");
    add_action("cmd_inv",     "i");
    add_action("cmd_equip",   "equip");
    add_action("cmd_equip",   "wear");
    add_action("cmd_equip",   "wield");
    add_action("cmd_unequip", "unequip");
    add_action("cmd_unequip", "remove");
    add_action("cmd_gear",    "gear");
    add_action("cmd_kill",    "kill");
    add_action("cmd_kill",    "attack");
    add_action("cmd_kill",    "k");
    add_action("cmd_flee",    "flee");
    add_action("cmd_get",     "get");
    add_action("cmd_get",     "take");
    add_action("cmd_drop",    "drop");
    add_action("cmd_examine", "examine");
    add_action("cmd_examine", "ex");
    add_action("cmd_help",    "help");
    add_action("cmd_quit",    "quit");
}

// ============================================================
// COMMANDS
// ============================================================
int cmd_look(string arg) {
    do_look();
    return 1;
}

int cmd_north(string arg) { return do_move("north"); }
int cmd_south(string arg) { return do_move("south"); }
int cmd_east(string arg)  { return do_move("east");  }
int cmd_west(string arg)  { return do_move("west");  }
int cmd_up(string arg)    { return do_move("up");    }
int cmd_down(string arg)  { return do_move("down");  }

int do_move(string dir) {
    object env = environment(this_object());
    if (!env) return 0;
    string dest = env->query_exit(dir);
    if (!dest) {
        write("You cannot go that way.\n");
        return 1;
    }
    move(dest);
    do_look();
    return 1;
}

int cmd_say(string arg) {
    if (!arg || !sizeof(arg)) { write("Say what?\n"); return 1; }
    tell_object(this_object(), C_WHITE + "You say: " + C_RESET + "'" + arg + "'\n");
    if (environment(this_object()))
        tell_room(environment(this_object()),
            C_WHITE + cap_str(query_name()) + " says: '" + arg + "'\n" + C_RESET,
            ({ this_object() }));
    return 1;
}

int cmd_tell(string arg) {
    if (!arg) { write("Tell who what?\n"); return 1; }
    string *parts = explode(arg, " ");
    if (sizeof(parts) < 2) { write("Tell " + parts[0] + " what?\n"); return 1; }
    string target = parts[0];
    string msg = implode(parts[1..], " ");
    object to = find_player(target);
    if (!to) { write("No player named '" + target + "' is online.\n"); return 1; }
    tell_object(to, C_MAGENTA + cap_str(query_name()) + " tells you: '" + msg + "'\n" + C_RESET);
    tell_object(this_object(), C_MAGENTA + "You tell " + cap_str(target) + ": '" + msg + "'\n" + C_RESET);
    return 1;
}

int cmd_who(string arg) {
    object *all = users();
    write(C_CYAN + repeat_string("=", 50) + C_RESET + "\n");
    write(C_LYELLOW + center_string("- Star Trek: Infinite Horizons -", 50) + C_RESET + "\n");
    write(C_CYAN + repeat_string("=", 50) + C_RESET + "\n");
    foreach (object p : all) {
        if (IS_PLAYER(p))
            write(sprintf("  %-15s  L%-3d  %-12s  %s\n",
                cap_str(p->query_name()),
                p->query_level(),
                cap_str(p->query_race()),
                cap_str(p->query_class())));
    }
    write(C_CYAN + repeat_string("=", 50) + C_RESET + "\n");
    write(sizeof(all) + " player(s) online.\n");
    return 1;
}

int cmd_score(string arg) {
    int pct_hp  = max_hp > 0 ? (query_hp() * 100 / max_hp) : 0;
    int pct_en  = max_energy > 0 ? (query_energy() * 100 / max_energy) : 0;
    write(C_CYAN + repeat_string("=", 60) + C_RESET + "\n");
    write(C_LYELLOW + " " + query_name() + " " + title + C_RESET + "\n");
    write(C_CYAN + repeat_string("-", 60) + C_RESET + "\n");
    write(sprintf(" Race: %-15s  Division: %s\n", cap_str(query_race()), cap_str(query_class())));
    write(sprintf(" Level: %-14d  XP: %d / %d\n", query_level(), query_xp(), query_xp_to_next()));
    write(sprintf(" HP:  %d/%d  [%s]\n", query_hp(), max_hp, health_bar(query_hp(), max_hp, 20)));
    write(sprintf(" Energy: %d/%d  [%s]\n", query_energy(), max_energy, health_bar(query_energy(), max_energy, 20)));
    write(C_CYAN + repeat_string("-", 60) + C_RESET + "\n");
    write(sprintf(" Kills: %-10d  Deaths: %d\n", total_kills, total_deaths));
    write(C_CYAN + repeat_string("=", 60) + C_RESET + "\n");
    return 1;
}

int cmd_stats(string arg) {
    write(C_CYAN + repeat_string("=", 50) + C_RESET + "\n");
    write(C_LYELLOW + " Character Statistics\n" + C_RESET);
    write(C_CYAN + repeat_string("-", 50) + C_RESET + "\n");
    write(C_LGREEN + " PRIMARY STATS\n" + C_RESET);
    string *ps = ALL_PRIMARY_STATS;
    foreach (string s : ps) {
        int base = query_base_stat(s);
        int total = query_total_stat(s);
        string gear_str = (total != base) ? (" (" + C_GREEN + total + C_RESET + ")") : "";
        write(sprintf("  %-15s %3d%s\n", cap_str(s) + ":", base, gear_str));
    }
    write(C_CYAN + repeat_string("-", 50) + C_RESET + "\n");
    write(C_LBLUE + " SECONDARY STATS\n" + C_RESET);
    write(sprintf("  %-20s %3d%%\n", "Crit Chance:", secondary_stats[STAT_CRIT_CHANCE]));
    write(sprintf("  %-20s %3d\n",   "Haste:", secondary_stats[STAT_HASTE]));
    write(sprintf("  %-20s %3d\n",   "Mastery:", secondary_stats[STAT_MASTERY]));
    write(sprintf("  %-20s %3d%%\n", "Versatility:", secondary_stats[STAT_VERSATILITY]));
    write(sprintf("  %-20s %3d%%\n", "Dodge:", secondary_stats[STAT_DODGE]));
    write(sprintf("  %-20s %3d\n",   "Armor:", secondary_stats[STAT_ARMOR]));
    write(sprintf("  %-20s %3d%%\n", "Hit Rating:", secondary_stats[STAT_HIT_RATING]));
    write(C_CYAN + repeat_string("=", 50) + C_RESET + "\n");
    return 1;
}

int cmd_inv(string arg) {
    write(C_YELLOW + "You are carrying:\n" + C_RESET);
    object ob = first_inventory(this_object());
    int count = 0;
    while (ob) {
        // Only show non-equipped items
        string slot = ob->query_slot();
        if (!slot || !query_equipped(slot) || query_equipped(slot) != ob) {
            write("  " + quality_name(ob->query_quality(), ob->query_short()) + "\n");
            count++;
        }
        ob = next_inventory(ob);
    }
    if (!count) write("  " + C_GREY + "(nothing)\n" + C_RESET);
    return 1;
}

int cmd_gear(string arg) {
    write(C_CYAN + repeat_string("=", 50) + C_RESET + "\n");
    write(C_LYELLOW + " Equipped Gear\n" + C_RESET);
    write(C_CYAN + repeat_string("-", 50) + C_RESET + "\n");
    string *slots = ALL_EQUIP_SLOTS;
    foreach (string slot : slots) {
        object item = query_equipped(slot);
        string item_str = item ? quality_name(item->query_quality(), item->query_short()) :
                          C_GREY + "(empty)" + C_RESET;
        write(sprintf("  %-12s %s\n", cap_str(slot) + ":", item_str));
    }
    write(C_CYAN + repeat_string("=", 50) + C_RESET + "\n");
    return 1;
}

int cmd_equip(string arg) {
    if (!arg) { write("Equip what?\n"); return 1; }
    object ob = present(arg, this_object());
    if (!ob) { write("You don't have '" + arg + "'.\n"); return 1; }
    if (!ob->is_equippable()) { write("You can't equip that.\n"); return 1; }
    if (equip_item(ob)) {
        write("You equip " + quality_name(ob->query_quality(), ob->query_short()) + ".\n");
        if (environment(this_object()))
            tell_room(environment(this_object()),
                cap_str(query_name()) + " equips " + ob->query_short() + ".\n",
                ({ this_object() }));
    } else {
        write("You can't equip that.\n");
    }
    return 1;
}

int cmd_unequip(string arg) {
    if (!arg) { write("Remove what?\n"); return 1; }
    // Find by slot name
    string *slots = ALL_EQUIP_SLOTS;
    foreach (string slot : slots) {
        object item = query_equipped(slot);
        if (item && id(item, arg)) {
            unequip_slot(slot);
            write("You remove " + quality_name(item->query_quality(), item->query_short()) + ".\n");
            return 1;
        }
    }
    write("You aren't wearing '" + arg + "'.\n");
    return 1;
}

int cmd_kill(string arg) {
    if (!arg) { write("Attack whom?\n"); return 1; }
    if (is_in_combat()) { write("You are already in combat!\n"); return 1; }
    object target = find_living_in_room(arg, environment(this_object()));
    if (!target || target == this_object()) {
        write("There's no '" + arg + "' here to attack.\n");
        return 1;
    }
    if (IS_PLAYER(target)) {
        write("You cannot attack other players here.\n");
        return 1;
    }
    write(C_LRED + "You attack " + cap_str(target->query_name()) + "!\n" + C_RESET);
    tell_room(environment(this_object()),
        cap_str(query_name()) + " attacks " + cap_str(target->query_name()) + "!\n",
        ({ this_object() }));
    enter_combat(target);
    target->enter_combat(this_object());
    return 1;
}

int cmd_flee(string arg) {
    if (!is_in_combat()) { write("You aren't in combat.\n"); return 1; }
    object env = environment(this_object());
    mapping exits = env->query_exits();
    if (!exits || !sizeof(exits)) {
        write("There's nowhere to flee to!\n");
        return 1;
    }
    string dir = m_indices(exits)[random(sizeof(exits))];
    string dest = exits[dir];
    leave_combat();
    write(C_YELLOW + "You flee " + dir + "!\n" + C_RESET);
    move(dest);
    do_look();
    return 1;
}

int cmd_get(string arg) {
    if (!arg) { write("Get what?\n"); return 1; }
    object ob = present(arg, environment(this_object()));
    if (!ob) { write("There's no '" + arg + "' here.\n"); return 1; }
    if (living(ob)) { write("You can't pick that up.\n"); return 1; }
    ob->move(this_object());
    write("You pick up " + ob->query_short() + ".\n");
    return 1;
}

int cmd_drop(string arg) {
    if (!arg) { write("Drop what?\n"); return 1; }
    object ob = present(arg, this_object());
    if (!ob) { write("You don't have '" + arg + "'.\n"); return 1; }
    ob->move(environment(this_object()));
    write("You drop " + ob->query_short() + ".\n");
    return 1;
}

int cmd_examine(string arg) {
    if (!arg) { cmd_look(""); return 1; }
    // Check inventory and room
    object ob = present(arg, this_object());
    if (!ob) ob = present(arg, environment(this_object()));
    if (!ob) { write("You don't see '" + arg + "' here.\n"); return 1; }
    ob->examine(this_object());
    return 1;
}

int cmd_help(string arg) {
    if (!arg) {
        write(C_CYAN + repeat_string("=", 60) + C_RESET + "\n");
        write(C_LYELLOW + center_string("HELP - Star Trek: Infinite Horizons", 60) + C_RESET + "\n");
        write(C_CYAN + repeat_string("-", 60) + C_RESET + "\n");
        write("MOVEMENT:  north/n, south/s, east/e, west/w, up/u, down/d\n");
        write("LOOK:      look/l, examine/ex <thing>\n");
        write("COMBAT:    kill/attack/k <target>, flee\n");
        write("ITEMS:     get/take <item>, drop <item>\n");
        write("GEAR:      inventory/inv/i, gear, equip/wear/wield <item>,\n");
        write("           unequip/remove <item>\n");
        write("CHARACTER: score/sc, stats\n");
        write("SOCIAL:    say/' <text>, tell <player> <text>, who\n");
        write("OTHER:     help <topic>, quit\n");
        write(C_CYAN + repeat_string("=", 60) + C_RESET + "\n");
        return 1;
    }
    write("No help available for '" + arg + "' yet.\n");
    return 1;
}

int cmd_quit(string arg) {
    write(C_LYELLOW + "Live long and prosper, " + query_name() + ".\n" + C_RESET);
    save_player();
    destruct(this_object());
    return 1;
}

// ============================================================
// DEATH
// ============================================================
void handle_death(object killer) {
    total_deaths++;
    tell_object(this_object(), C_RED +
        "\n*** You have been killed! ***\n" +
        "You wake up in Starfleet Medical...\n" + C_RESET);
    // Lose 10% of current XP
    int xp_loss = query_xp() / 10;
    gain_xp(-xp_loss);
    if (xp_loss > 0)
        tell_object(this_object(), C_RED + "You lose " + xp_loss + " experience points.\n" + C_RESET);
    // Respawn
    set_hp(max_hp / 2);
    set_energy(max_energy / 2);
    move("/d/starfleet/rooms/medical_bay");
    do_look();
    save_player();
}
