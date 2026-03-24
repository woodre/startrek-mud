/* /secure/login.c
 * Login handler for Star Trek: Infinite Horizons
 * Handles new connections, login, and character creation
 */

#include "/include/mudlib.h"
#include "/include/races.h"

string name;
int new_player;
int creation_stage;
string race_choice;
string class_choice;

// Called when object is connected to as a player
void logon() {
    write("\n");
    write(C_CYAN + repeat_string("=", 70) + C_RESET + "\n");
    cat(WELCOME_FILE);
    write(C_CYAN + repeat_string("=", 70) + C_RESET + "\n\n");
    write(C_YELLOW + "By what name do you wish to be known? " + C_RESET);
    input_to("get_name");
}

// Receive the player's name
void get_name(string str) {
    if (!str || !strlen(str)) {
        write(C_RED + "Please enter a name.\n" + C_RESET);
        write("By what name do you wish to be known? ");
        input_to("get_name");
        return;
    }
    str = lower_case(str);
    // Validate name: letters only, 3-12 chars
    if (strlen(str) < 3 || strlen(str) > 12) {
        write(C_RED + "Name must be between 3 and 12 characters.\n" + C_RESET);
        write("By what name do you wish to be known? ");
        input_to("get_name");
        return;
    }
    int i;
    for (i = 0; i < strlen(str); i++) {
        int c = str[i];
        if (!((c >= 'a' && c <= 'z'))) {
            write(C_RED + "Name must contain only letters.\n" + C_RESET);
            write("By what name do you wish to be known? ");
            input_to("get_name");
            return;
        }
    }
    name = cap_str(str);
    // Check if player file exists
    if (file_size(PLAYER_SAVE_DIR + lower_case(name) + ".o") > 0) {
        new_player = 0;
        write("\nWelcome back, " + C_LGREEN + name + C_RESET + "!\n");
        write("Password: ");
        input_to("get_password", 1);
    } else {
        new_player = 1;
        write("\nA new face aboard the station! Welcome, " + C_LGREEN + name + C_RESET + ".\n");
        write("Choose a password: ");
        input_to("get_new_password", 1);
    }
}

// Existing player - verify password
void get_password(string pass) {
    if (!pass || !strlen(pass)) {
        write("Password: ");
        input_to("get_password", 1);
        return;
    }
    object player = clone_object(PLAYER_OB);
    player->set_name(name);
    if (!player->load_player(pass)) {
        destruct(player);
        write(C_RED + "\nIncorrect password. Try again.\n" + C_RESET);
        write("Password: ");
        input_to("get_password", 1);
        return;
    }
    // Successful login
    exec(player, this_object());
    player->setup_after_login();
    destruct(this_object());
}

// New player - set password
void get_new_password(string pass) {
    if (!pass || strlen(pass) < 5) {
        write(C_RED + "Password must be at least 5 characters.\n" + C_RESET);
        write("Choose a password: ");
        input_to("get_new_password", 1);
        return;
    }
    object player = clone_object(PLAYER_OB);
    player->set_name(name);
    player->set_password(crypt(pass, 0));
    creation_stage = 1;
    exec(player, this_object());
    player->start_creation();
    destruct(this_object());
}
