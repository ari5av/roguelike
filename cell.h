#ifndef CELL_H
#define CELL_H

#include "feature.h"
#include "item.h"

typedef enum _terrain_t {
  TL_STONE = 1, // standard
  TL_BRICK,     // standard
  TL_GRASS,     // nature spells work better over grass
  TL_WOOD,
  TL_GRAVEL,    // more likely to make noise when moving over
                // gravel (or wood, if wearing non-leather shoes)
  TL_SAND,      // move slower, cannot move when at max burden
  TL_SNOW,      // move slower, cannot move at any level of burden
                // cold spells work better on snow
  TL_DIRT,      // move slower, but can move at max burden
  TL_WATER,     // requires feature FT_SPRING, FT_POOL, FT_POND,
                // FT_LAKE, or FT_RIVER
  TL_LAVA,      // requires feature FT_LAVA or FT_FIRE
  TL_WALL,      // standard wall, impermeable (for level borders)
                // note: normal walls in the level are over stone,
                // dirt, or wood (for digging out the wall)
} terrain_t;

typedef struct _Cell {
  terrain_t floor;
  Feature *feature;
  int item_count;
  Item **item_list;
} Cell;

#endif