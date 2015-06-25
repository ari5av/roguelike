#ifndef ITEM_H
#define ITEM_H

typedef struct _Item {
  struct _Item * next;
  char name[40];
} Item;

#endif