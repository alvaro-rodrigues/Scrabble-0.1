#ifndef BAG_H
#define BAG_H

typedef struct bag_node {
  char data;
  struct bag_node *next;
} bag_node_t;

typedef struct {
  bag_node_t *head;
  bag_node_t *tail;
  int n_elements;
} bag_t;

bag_t *bagCreate();
void bagInsert(bag_t *bag, char data);
void bagFill(bag_t *bag);
char bagRemove(bag_t *bag);
int bagIsEmpty(bag_t *bag);

#endif
