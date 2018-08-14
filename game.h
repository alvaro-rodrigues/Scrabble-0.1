#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "bag.h"
#include "board.h"

typedef struct node {
  player_t *player;
  struct node *next;
} node_t;

typedef struct {
  node_t *first;
  node_t *last;
  int num_elements;
} game_t;

game_t *gameCreate();
void playerAdd(game_t *game, player_t *player);
void gameStart(game_t *t, bag_t *bag);
void swap(int *values, int i, int j);
void insertion2(int *scores, int *players, int n);
void gameScoreBoard(game_t *game);
void gameRound(game_t *game, node_t *node, player_t *player, bag_t *bag, board_t *board, int jump);


#endif
