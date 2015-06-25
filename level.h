#include "cell.h"

typedef struct _Level {
  char * name;
  int x_size;
  int y_size;
  Cell * map[];
} Level;