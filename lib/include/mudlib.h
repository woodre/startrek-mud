/* mudlib.h - Global mudlib defines and paths */

#ifndef MUDLIB_H
#define MUDLIB_H

/* Core paths */
#define MASTER_OB       "/secure/master"
#define LOGIN_OB        "/secure/login"
#define PLAYER_OB       "/std/player"
#define ROOM_OB         "/std/room"
#define MONSTER_OB      "/std/monster"
#define ITEM_OB         "/std/item"
#define WEAPON_OB       "/std/weapon"
#define ARMOR_OB        "/std/armor"
#define CORPSE_OB       "/obj/corpse"

/* Simul efun path */
#define SIMUL_EFUN      "/secure/simul_efun"

/* Save file paths */
#define PLAYER_SAVE_DIR "/secure/players/"
#define LOG_DIR         "/log/"

/* Mud name and info */
#define MUD_NAME        "Star Trek: Infinite Horizons"
#define MUD_VERSION     "1.0"
#define WELCOME_FILE    "/secure/WELCOME"
#define MOTD_FILE       "/secure/MOTD"

/* Useful macros */
#define IS_PLAYER(ob)   (objectp(ob) && ob->is_player())
#define IS_WIZARD(ob)   (objectp(ob) && ob->query_level() >= 60)
#define IS_LIVING(ob)   (objectp(ob) && living(ob))

/* Color codes (ANSI) */
#define C_RESET         "\033[0m"
#define C_BOLD          "\033[1m"
#define C_RED           "\033[31m"
#define C_GREEN         "\033[32m"
#define C_YELLOW        "\033[33m"
#define C_BLUE          "\033[34m"
#define C_MAGENTA       "\033[35m"
#define C_CYAN          "\033[36m"
#define C_WHITE         "\033[37m"
#define C_GREY          "\033[90m"
#define C_ORANGE        "\033[38;5;214m"
#define C_LRED          "\033[91m"
#define C_LGREEN        "\033[92m"
#define C_LYELLOW       "\033[93m"
#define C_LBLUE         "\033[94m"
#define C_LMAGENTA      "\033[95m"
#define C_LCYAN         "\033[96m"

#include "/include/stats.h"
#include "/include/races.h"

#endif /* MUDLIB_H */
