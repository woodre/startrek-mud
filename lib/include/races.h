/* races.h - Star Trek race definitions */

#ifndef RACES_H
#define RACES_H

/* Playable races */
#define RACE_HUMAN           "human"
#define RACE_VULCAN          "vulcan"
#define RACE_KLINGON         "klingon"
#define RACE_BETAZOID        "betazoid"
#define RACE_ANDORIAN        "andorian"
#define RACE_BAJORAN         "bajoran"
#define RACE_FERENGI         "ferengi"
#define RACE_TRILL           "trill"
#define RACE_CARDASSIAN      "cardassian"
#define RACE_BOLIAN          "bolian"

#define ALL_RACES ({ RACE_HUMAN, RACE_VULCAN, RACE_KLINGON, RACE_BETAZOID, \
                     RACE_ANDORIAN, RACE_BAJORAN, RACE_FERENGI, RACE_TRILL, \
                     RACE_CARDASSIAN, RACE_BOLIAN })

/* Playable classes (WoW-inspired, Star Trek themed) */
#define CLASS_TACTICAL       "tactical"      // DPS/Tank - Security/Combat
#define CLASS_SCIENCE        "science"       // Healer/Caster - Science/Medical  
#define CLASS_ENGINEERING    "engineering"   // Support/Tank - Engineering
#define CLASS_OPERATIONS     "operations"    // DPS/Support - Multi-role
#define CLASS_COMMAND        "command"       // Leader/Buffer - Leadership auras

#define ALL_CLASSES ({ CLASS_TACTICAL, CLASS_SCIENCE, CLASS_ENGINEERING, \
                       CLASS_OPERATIONS, CLASS_COMMAND })

/* Starting zones by race */
#define START_ZONE_HUMAN       "/d/starfleet/rooms/academy_entrance"
#define START_ZONE_VULCAN      "/d/starfleet/rooms/vulcan_embassy"
#define START_ZONE_KLINGON     "/d/klingon/rooms/warrior_hall"
#define START_ZONE_BETAZOID    "/d/starfleet/rooms/counselor_office"
#define START_ZONE_ANDORIAN    "/d/starfleet/rooms/andorian_quarter"
#define START_ZONE_BAJORAN     "/d/bajor/rooms/temple_entrance"
#define START_ZONE_FERENGI     "/d/starfleet/rooms/commerce_deck"
#define START_ZONE_TRILL       "/d/starfleet/rooms/symbiosis_ward"
#define START_ZONE_CARDASSIAN  "/d/starfleet/rooms/civilian_docking"
#define START_ZONE_BOLIAN      "/d/starfleet/rooms/civilian_docking"

#endif /* RACES_H */
