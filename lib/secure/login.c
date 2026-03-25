/* /secure/login.c
 * Login handler - uses only native LDMud efuns
 */

#include "/include/mudlib.h"

string name;
int new_player;
string pending_pass;

void logon() {
    write(read_file(WELCOME_FILE) || "Welcome!\n");
    write("By what name do you wish to be known? ");
    input_to("get_name");
}

void get_name(string str) {
    if (!str || !sizeof(str)) {
        write("Please enter a name.\n");
        write("By what name do you wish to be known? ");
        input_to("get_name");
        return;
    }
    str = lower_case(str);
    if (sizeof(str) < 3 || sizeof(str) > 12) {
        write("Name must be between 3 and 12 characters.\n");
        write("By what name do you wish to be known? ");
        input_to("get_name");
        return;
    }
    // Letters only
    int i;
    for (i = 0; i < sizeof(str); i++) {
        int c = str[i];
        if (c < 'a' || c > 'z') {
            write("Name must contain only letters.\n");
            write("By what name do you wish to be known? ");
            input_to("get_name");
            return;
        }
    }
    name = upper_case(str[0..0]) + str[1..];
    if (file_size(PLAYER_SAVE_DIR + lower_case(name) + ".o") > 0) {
        new_player = 0;
        write("Welcome back, " + name + "!\n");
        write("Password: ");
        input_to("get_password", 1);
    } else {
        new_player = 1;
        write("Welcome, " + name + "! This appears to be a new character.\n");
        write("Choose a password: ");
        input_to("get_new_password", 1);
    }
}

void get_password(string pass) {
    if (!pass || !sizeof(pass)) {
        write("Password: ");
        input_to("get_password", 1);
        return;
    }
    object player = clone_object(PLAYER_OB);
    player->set_name(name);
    if (!player->load_player(pass)) {
        destruct(player);
        write("Incorrect password.\n");
        write("Password: ");
        input_to("get_password", 1);
        return;
    }
    exec(player, this_object());
    player->setup_after_login();
    destruct(this_object());
}

void get_new_password(string pass) {
    if (!pass || sizeof(pass) < 5) {
        write("Password must be at least 5 characters.\n");
        write("Choose a password: ");
        input_to("get_new_password", 1);
        return;
    }
    pending_pass = pass;
    write("Confirm password: ");
    input_to("confirm_new_password", 1);
}

void confirm_new_password(string pass) {
    if (pass != pending_pass) {
        write("Passwords do not match.\n");
        write("Choose a password: ");
        input_to("get_new_password", 1);
        return;
    }
    object player = clone_object(PLAYER_OB);
    player->set_name(name);
    player->set_password(crypt(pass, 0));
    exec(player, this_object());
    player->start_creation();
    destruct(this_object());
}
