#ifndef PALYER_H
#define PALYER_H
#include "bag.h"

#define MAX_SIZE 7

typedef struct {
  int n_elements;
  int score;
  int p_number;
  int titles;
  char *data;
} player_t;

player_t *playerCreate();
void playerInsert(player_t *player, bag_t *bag);
void playerFill(player_t *player, bag_t *bag);
void playerScore(player_t *player, char c);
void playerRebuy(player_t *player, bag_t *bag);
void playerPrint(player_t *player);

#endif
