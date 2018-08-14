#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "bag.h"

bag_t *bagCreate() {
  bag_t *bag = (bag_t *) malloc(sizeof(bag_t));
  if (bag == NULL) {
    printf("Erro, sem memória!!");
    exit(1);
  }
  bag->head = NULL;
  bag->tail = NULL;
  bag->n_elements = 0;
  return bag;
}

void bagInsert(bag_t *bag, char data) {
  bag_node_t *node = (bag_node_t *) malloc(sizeof(bag_node_t));
  if (node == NULL) {
    printf("Erro, sem memória!!");
    exit(1);
  }
  node->data = data;
  node->next = NULL;
  bag->n_elements++;
  if (bag->head == NULL) {
    bag->head = node;
    bag->tail = node;
  } else {
    bag->tail->next = node;
    bag->tail = node;
  }
}

void bagFill(bag_t *bag) {
  char letters[] = {'A','B','C','D','E','F','G','H','I','J','L','M','N','O','P','Q','R','S','T','U','V','X','Z'};
  int counts[] = {14, 3, 4, 5, 11, 2, 2, 2, 10, 2, 5, 6, 4, 10, 4, 1, 6, 8, 5, 7, 2, 1, 1};
  srand(time(NULL));
  while (bag->n_elements != 115) {
    int index = rand() % 23;
    if (counts[index] > 0) {
      bagInsert(bag, letters[index]);
      counts[index]--;
    }
  }
}

char bagRemove(bag_t *bag) {
  bag_node_t *toFree;
  char toReturn;
  if (bag->head != NULL) {
    toReturn = bag->head->data;
    toFree = bag->head;
    bag->head = bag->head->next;
    free(toFree);
    bag->n_elements--;
  } else {
    printf("O saco esta vazio");
    exit(1);
  }
  return toReturn;
}

int bagIsEmpty(bag_t *bag) {
  if (bag->head == NULL) {
    return 1;
  } else {
    return 0;
  }
}
