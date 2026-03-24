/* /secure/master.c
 * Master object for Star Trek: Infinite Horizons
 * LDMud 3.6.x compatible - uses only standard efuns
 */

// Called when driver first loads
void create() {
}

// Return the simul_efun object path
string get_simul_efun() {
    return "/secure/simul_efun";
}

// Called for each new incoming connection - return login object
object connect(int port) {
    object login;
    login = clone_object("/secure/login");
    return login;
}

// Called when a connection disconnects unexpectedly
void disconnect(object ob) {
    if (ob && ob->is_player()) {
        ob->save_player();
    }
}

// Access control
int valid_read(string path, mixed caller, string func) {
    return 1;
}

int valid_write(string path, mixed caller, string func) {
    return 1;
}

// Called when a runtime error occurs
void runtime_error(string err, string prg, string curobj, int line,
                   mixed culprit, int caught) {
    if (this_player()) {
        if (this_player()->query_level() >= 60)
            tell_object(this_player(),
                "Runtime error: " + err + " in " + prg + " line " + line + "\n");
        else
            tell_object(this_player(),
                "A minor anomaly was detected.\n");
    }
}

// Privilege verification - return 1 to allow, 0 to deny
int privilege_violation(string op, mixed who, varargs mixed *args) {
    return 1;
}

// Called to get the include search path
string *get_include_path(string base_file) {
    return ({ "/include", "/" });
}

// Called by the driver for object not found errors
string object_not_found(string file) {
    return 0;
}

// Called before an object is destructed
void prepare_destruct(object ob) {
    if (ob->is_player())
        ob->save_player();
}

// Preload any objects at startup (optional)
void preload(closure func) {
    // Nothing to preload at startup
}

// Handle incoming telnet connections
void logon(object ob) {
}

// Flag function called before connections are accepted
void flag(string arg) {
}

// Called when the driver is shutting down
void notify_shutdown() {
}
