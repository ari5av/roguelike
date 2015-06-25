#include "item.h"

typedef enum _alignment_t {
  AL_LAW = 1,
  AL_BALANCE = 0,
  AL_CHAOS = -1
} alignment_t;

typedef enum _feature_t {
  // features you can see, walk, or levitate through
  FT_ALTAR = 1,         // can #pray or #sacrifice
  FT_ARMORRACK,         // holds wearable items
  FT_BARREL,            // holds one type of item
                        // flammable
  FT_BARS_OPEN,         // slow movement, cannot move through diagonally
  FT_BED,               // can #sleep
                        // flammable
  FT_BOOKSHELF,         // holds readable items
                        // flammable
  FT_BOX,               // holds items
                        // flammable
  FT_CASK,              // holds one type of drinkable item
                        // flammable
  FT_CHAIR,             // can #sit which causes extra nutrition when
                        // #eat-ing
                        // flammable
  FT_CHEST,             // holds items
                        // flammable
  FT_CHUTE,             // teleports to a lower level
  FT_COFFIN,            // holds one corpse
                        // flammable
  FT_COUCH,             // can #sit or #sleep, #sit-ting causes extra
                        // nutrition when #eat-ing
                        // flammable
  FT_DOOR_OPEN,         // can be #close-d, cannot move through diagonally
  FT_FLOWER,            // can be #harvest-ed
                        // flammable
  FT_FONT,              // can #drink
  FT_FOUNTAIN,          // can #drink
  FT_GRAVESTONE,        // can #dig to reveal one corpse and several items
  FT_HERB,              // can be #harvest-ed
                        // flammable
  FT_LAMP,              // gives light
                        // can #light or #extinguish
  FT_PEDESTAL,          // decoration only?
  FT_PLANT,             // can be #harvest-ed
                        // flammable
  FT_PORTAL,            // teleports to anywhere
  FT_PORTCULLIS_OPEN,   // can be #close-d, cannot move through diagonally
  FT_SARCOPHAGUS,       // holds one corpse
  FT_SCONCE,            // gives light
  FT_SHRINE,            // can #pray
  FT_SINK,              // can #drink or #use to fill empty water bottles
  FT_STAIRS_DN,         // teleports one level down
  FT_STAIRS_UP,         // teleports one level up
  FT_STRONGBOX,         // holds items
  FT_THRONE,            // can #sit, does not cause extra nutrition when
                        // #eat-ing (unless near a table)
  FT_TRAP,              // can #untrap if nearby
  FT_WEAPONRACK,        // holds equippable items
  FT_WELL,              // can #drink

  // features you can see through but can only swim or levitate
  // through
  FT_LAKE,              // boats work
  FT_POND,              // boats work
  FT_POOL,              // boats do not work
  FT_RIVER,             // boats work
  FT_SPRING,            // can #drink next to a spring
  
  // features you can see through but cannot move through
  FT_BARS_CLOSED,       // can #open with a strength check
  FT_BUSH,              // chance to take damage on attempted move
  FT_CAGE,              // generally used as walls, with bars for a door
  FT_COLUMN,            // decoration only
  FT_FIRE,              // can randomly spread to nearby cells,
                        // destroying features and items, gives light
  FT_FIREPLACE,         // can #cook food items, gives light
  FT_FORGE,             // can #use to smelt ore, can #craft metal items,
                        // gives light
  FT_FURNACE,           // can #cook food items, can #craft metal items
  FT_HIVE,              // causes bees to spawn nearby
  FT_ICEBLOCK,          // destroyed when fire is nearby or applied
  FT_IRONMAIDEN,        // holds one corpse
  FT_LAVA,
  FT_NEST,              // causes one kind of enemy to spawn nearby
  FT_OVEN,              // can #cook food items
  FT_PILE_GRAVEL,       // decoration only
  FT_PILE_ROCKS,        // decoration only
  FT_PILE_RUBBLE,       // decoration only
  FT_PILLAR,            // decoration only
  FT_PORTCULLIS_CLOSED, // can be #open-ed, cannot move through
                        // diagonally
  FT_STATUE,            // decoration only
  FT_STALAGMITE,        // decoration only
  FT_TABLE,             // if #sit-ting nearby, causes extra nutrition
                        // when #eat-ing
  FT_TREE,              // can be #chop-ped down for wood
  FT_WINDOW,            // decoration only

  // features you cannot see or move through
  FT_DOOR_CLOSED,       // can be #open-ed or #lock-ed or #unlocked,
                        // cannot move through diagonally
  FT_MINERALVEIN,       // can #dig for a chance to drop ore
  FT_WALL,              // decoration only

  // special feature, must be over a TL_WALL
  FT_IMPERMEABLE
} feature_t;

// @TODO flesh this out
typedef enum _trap_t {
  TR_FIRE = 1,
  TR_PIT
} trap_t;

// @TODO flesh out and move
typedef enum _enemy_t {
  EN_ANIMAL = 1,
  EN_HUMANOID,
  EN_GOBLINOID,
  EN_ABERRATION
} enemy_t;

typedef struct _Feature {
  feature_t type;

  // traps
  trap_t trap_type;

  // hives, nests
  enemy_t enemy_spawn_type;
  int enemy_spawn_radius;
  int enemy_spawn_freq;       // one will spawn every n ticks

  // booleans
  int can_walk;
  int can_swim;
  int can_sail;
  int can_levitate;
  int blocks_light;
  int is_flammable;
  int is_container;

  // may be unseen, but do I know it's there?
  int is_known;

  // how fast do you move in and out of the tile?
  // 0.5 for most, 1 or more for slow-movement tiles
  float walk_speed_in;
  float walk_speed_out;
  float swim_speed_in;
  float swim_speed_out;
  float sail_speed_in;
  float sail_speed_out;
  float lev_speed_in;
  float lev_speed_out;
  int can_move_diagonally;

  // doors, portcullises, bars, sarcophagi, coffins, boxes,
  // chests, strongboxes, iron maidens
  int is_open;
  int is_unlocked;
  int can_lock;
  int can_close;

  // portals, chutes
  struct _Level * ports_to_level;
  int ports_to_x;
  int ports_to_y;

  // altars, shrines
  alignment_t alignment;

  // containers
  int contained_types;  // bitfield: item types a container can hold
  int item_count;
  Item **item_list;

  // lamps, sconces, fire, fireplaces, forges
  int is_lit;
  int illumination_radius;

} Feature;