/* /secure/master.c
 * Master object for Star Trek: Infinite Horizons
 * Handles driver<->mudlib gateway functions
 */

#include "/include/mudlib.h"

// Called when driver first loads
void create() {
    seteuid("root");
}

// Return the simul_efun object path
string get_simul_efun() {
    return SIMUL_EFUN;
}

// Called for each new incoming connection - return login object
object connect(int port) {
    object login;
    login = clone_object(LOGIN_OB);
    return login;
}

// Called when a connection disconnects unexpectedly
void disconnect(object ob) {
    if (ob && IS_PLAYER(ob)) {
        ob->save_player();
        log_file(LOG_DIR + "disconnect", ctime(time()) + " " + ob->query_name() + " disconnected\n");
    }
}

// Access control - what files can be read/written
int valid_read(string path, object caller, string func) {
    // Wizards can read everything
    if (IS_WIZARD(this_player()))
        return 1;
    // Players can only read/write their own save file
    if (func == "restore_object" || func == "save_object") {
        if (strsrch(path, PLAYER_SAVE_DIR) == 0)
            return 1;
    }
    // Allow reading of rooms, objects etc
    if (strsrch(path, "/d/") == 0 || strsrch(path, "/std/") == 0 ||
        strsrch(path, "/obj/") == 0 || strsrch(path, "/secure/WELCOME") == 0 ||
        strsrch(path, "/secure/MOTD") == 0)
        return 1;
    return 0;
}

int valid_write(string path, object caller, string func) {
    if (IS_WIZARD(this_player()))
        return 1;
    if (func == "save_object") {
        if (strsrch(path, PLAYER_SAVE_DIR) == 0)
            return 1;
    }
    if (strsrch(path, LOG_DIR) == 0)
        return 1;
    return 0;
}

// Called when a runtime error occurs
void runtime_error(string err, string prg, string curobj, int line, mixed culprit, int caught) {
    log_file(LOG_DIR + "runtime_errors",
        sprintf("[%s] ERROR in %s (line %d) running %s: %s\n",
            ctime(time()), prg, line, curobj, err));
    if (this_player()) {
        if (IS_WIZARD(this_player()))
            tell_object(this_player(), C_RED + "Runtime error: " + err + 
                        " in " + prg + " line " + line + C_RESET + "\n");
        else
            tell_object(this_player(), C_RED + "A minor anomaly was detected and logged.\n" + C_RESET);
    }
}

// Driver calls this to compile objects - return modified source or 0
mixed include_file(string file, string compiled_file) {
    return 0;
}

// Return the error message for object not found
string object_not_found(string file) {
    return "Object " + file + " not found.\n";
}

// Handle calls to undefined functions - for compatibility
mixed call_strict(mixed ob, string func, varargs mixed *args) {
    return 0;
}

// Called when player object is created to notify master
void log_player(string name) {
    log_file(LOG_DIR + "logins", ctime(time()) + " " + name + " logged in\n");
}

// Privilege verification
int privilege_violation(string op, mixed who, varargs mixed *args) {
    // Root-level operations
    if (geteuid(who) == "root")
        return 1;
    if (op == "erq" || op == "shutdown")
        return IS_WIZARD(who);
    return 0;
}

// Return list of auto-included headers
string *get_include_path(string base_file) {
    return ({ "/include" });
}
