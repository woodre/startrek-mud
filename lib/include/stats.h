/* stats.h - Core stat definitions for Star Trek MUD
 * WoW-style primary and secondary stat system
 */

#ifndef STATS_H
#define STATS_H

/* ============================================================
 * PRIMARY STATS
 * ============================================================ */
#define STAT_STRENGTH        "strength"       // Melee damage, carry weight
#define STAT_AGILITY         "agility"        // Dodge, ranged attack speed
#define STAT_INTELLECT       "intellect"      // Psionic/tech power, energy pool
#define STAT_STAMINA         "stamina"        // HP pool (1 stamina = 10 HP)
#define STAT_SPIRIT          "spirit"         // HP/Energy regen rate
#define STAT_PRESENCE        "presence"       // Diplomacy, vendor pricing, leadership

#define ALL_PRIMARY_STATS ({ STAT_STRENGTH, STAT_AGILITY, STAT_INTELLECT, \
                              STAT_STAMINA, STAT_SPIRIT, STAT_PRESENCE })

/* ============================================================
 * SECONDARY STATS (derived or on-gear)
 * ============================================================ */
#define STAT_CRIT_CHANCE     "crit_chance"    // % chance to deal double damage
#define STAT_HASTE           "haste"          // Reduces action round time
#define STAT_MASTERY         "mastery"        // Boosts class-specific mechanic
#define STAT_VERSATILITY     "versatility"    // % bonus to all damage and healing
#define STAT_DODGE           "dodge"          // % chance to avoid attack entirely
#define STAT_ARMOR           "armor"          // Flat physical damage reduction
#define STAT_ENERGY_REGEN    "energy_regen"   // Energy/shields regen per round
#define STAT_HIT_RATING      "hit_rating"     // Reduces miss chance

#define ALL_SECONDARY_STATS ({ STAT_CRIT_CHANCE, STAT_HASTE, STAT_MASTERY, \
                                STAT_VERSATILITY, STAT_DODGE, STAT_ARMOR, \
                                STAT_ENERGY_REGEN, STAT_HIT_RATING })

/* ============================================================
 * DERIVED STATS (calculated at runtime)
 * ============================================================ */
#define STAT_MAX_HP          "max_hp"
#define STAT_MAX_ENERGY      "max_energy"     // Shields / Psionic energy
#define STAT_ATTACK_POWER    "attack_power"
#define STAT_RANGED_POWER    "ranged_power"
#define STAT_TECH_POWER      "tech_power"     // For science/tech abilities

/* ============================================================
 * STAT SCALING CONSTANTS
 * ============================================================ */
#define HP_PER_STAMINA       10
#define ENERGY_PER_INTELLECT 15
#define AP_PER_STRENGTH      2
#define RP_PER_AGILITY       2
#define TP_PER_INTELLECT     2
#define CRIT_PER_AGI         0.05     // 0.05% crit per agility (as float *100)
#define BASE_CRIT            5        // 5% base crit chance
#define BASE_HIT             95       // 95% base hit chance
#define BASE_DODGE           5        // 5% base dodge chance

/* ============================================================
 * EQUIPMENT SLOTS (WoW-style)
 * ============================================================ */
#define SLOT_HEAD            "head"
#define SLOT_NECK            "neck"
#define SLOT_SHOULDER        "shoulder"
#define SLOT_BACK            "back"
#define SLOT_CHEST           "chest"
#define SLOT_WRIST           "wrist"
#define SLOT_HANDS           "hands"
#define SLOT_WAIST           "waist"
#define SLOT_LEGS            "legs"
#define SLOT_FEET            "feet"
#define SLOT_FINGER1         "finger1"
#define SLOT_FINGER2         "finger2"
#define SLOT_TRINKET1        "trinket1"
#define SLOT_TRINKET2        "trinket2"
#define SLOT_MAINHAND        "mainhand"
#define SLOT_OFFHAND         "offhand"
#define SLOT_RANGED          "ranged"        // Phaser rifle / bow equivalent

#define ALL_EQUIP_SLOTS ({ SLOT_HEAD, SLOT_NECK, SLOT_SHOULDER, SLOT_BACK, \
                           SLOT_CHEST, SLOT_WRIST, SLOT_HANDS, SLOT_WAIST, \
                           SLOT_LEGS, SLOT_FEET, SLOT_FINGER1, SLOT_FINGER2, \
                           SLOT_TRINKET1, SLOT_TRINKET2, SLOT_MAINHAND, \
                           SLOT_OFFHAND, SLOT_RANGED })

/* ============================================================
 * ITEM QUALITY (WoW-style color tiers)
 * ============================================================ */
#define QUALITY_POOR         0    // Grey  - vendor trash
#define QUALITY_COMMON       1    // White - standard issue
#define QUALITY_UNCOMMON     2    // Green - enhanced
#define QUALITY_RARE         3    // Blue  - superior
#define QUALITY_EPIC         4    // Purple - exceptional
#define QUALITY_LEGENDARY    5    // Orange - legendary artifacts

#define QUALITY_NAME(q) ( (q)==0 ? "Poor" : (q)==1 ? "Common" : \
                          (q)==2 ? "Uncommon" : (q)==3 ? "Rare" : \
                          (q)==4 ? "Epic" : "Legendary" )

#define QUALITY_COLOR(q) ( (q)==0 ? "%^GREY%^" : (q)==1 ? "%^WHITE%^" : \
                           (q)==2 ? "%^GREEN%^" : (q)==3 ? "%^CYAN%^" : \
                           (q)==4 ? "%^MAGENTA%^" : "%^ORANGE%^" )

/* ============================================================
 * ITEM TYPES
 * ============================================================ */
#define ITYPE_ARMOR          "armor"
#define ITYPE_WEAPON         "weapon"
#define ITYPE_TRINKET        "trinket"
#define ITYPE_CONSUMABLE     "consumable"
#define ITYPE_QUEST          "quest"
#define ITYPE_MISC           "misc"

/* ============================================================
 * WEAPON TYPES
 * ============================================================ */
#define WTYPE_PHASER         "phaser"        // 1H ranged - standard sidearm
#define WTYPE_PHASER_RIFLE   "phaser_rifle"  // 2H ranged - heavy damage
#define WTYPE_DISRUPTOR      "disruptor"     // Klingon/Romulan ranged
#define WTYPE_BATLET         "batlet"        // Klingon melee 2H
#define WTYPE_MEKLETH        "mekleth"       // Klingon melee 1H
#define WTYPE_LIRPA          "lirpa"         // Vulcan ceremonial 2H
#define WTYPE_USHAAN_TOR     "ushaan_tor"    // Andorian melee 1H
#define WTYPE_DAGGER         "dagger"        // Generic melee 1H
#define WTYPE_STAFF          "staff"         // Psionic focus 2H
#define WTYPE_TARG_WHIP      "targ_whip"     // Klingon unique 1H

/* ============================================================
 * ARMOR TYPES
 * ============================================================ */
#define ATYPE_UNIFORM        "uniform"       // Cloth equiv - Science/Medical
#define ATYPE_LIGHT          "light"         // Leather equiv - Ops/Engineering
#define ATYPE_MEDIUM         "medium"        // Mail equiv - Security
#define ATYPE_HEAVY          "heavy"         // Plate equiv - Warrior/Klingon

/* ============================================================
 * COMBAT CONSTANTS
 * ============================================================ */
#define COMBAT_ROUND_TIME    3              // Seconds per combat round
#define XP_BASE              100
#define XP_MULTIPLIER        1.5
#define MAX_LEVEL            60
#define LEVEL_STAT_BONUS     5             // Stats gained per level

#endif /* STATS_H */
