#include <stdlib.h>
#include <stdio.h>
#include "player.h"

player_t *playerCreate() {
  char *data = (char *) malloc(MAX_SIZE * sizeof(char));
  if (data == NULL) {
    printf("Erro, sem memória!!");
    exit(1);
  }
  player_t *player = (player_t *) malloc(sizeof(player_t));
  if (player == NULL) {
    printf("Erro, sem memória!!");
    exit(1);
  }
  player->data = data;
  player->n_elements = 0;
  player->score = 0;
  return player;
}

void playerInsert(player_t *player, bag_t *bag) {
  if (player->n_elements == MAX_SIZE) {
    printf("Erro, mão cheia!!");
    exit(1);
  }
  char data = bagRemove(bag);
  player->data[player->n_elements] = data;
  player->n_elements++;
}

void playerFill(player_t *player, bag_t *bag) {
  while (player->n_elements != MAX_SIZE) {
    playerInsert(player, bag);
  }
  player->titles = 7;
}

void playerScore(player_t *player, char c) {
  char letters[] = {'A','B','C','D','E','F','G','H','I','J','L','M','N','O','P','Q','R','S','T','U','V','X','Z'};
  int values[] = {1, 3, 2, 2, 1, 4, 4, 4, 1, 5, 2, 1, 3, 1, 2, 1, 1, 1, 1, 1, 4, 8, 8};
  int i;
  for (i = 0; i < 23; i++) {
    if (c == letters[i]) {
      break;
    }
  }
  player->score += values[i];
}

void playerRebuy(player_t *player, bag_t *bag) {
  int i;
  for (i = 0; i < MAX_SIZE; i++) {
    if (player->data[i] == '\0' && bag->head != NULL) {
      player->data[i] = bagRemove(bag);
      player->titles++;
    }
  }
}

void playerPrint(player_t *player) {
  int i;
  for(i = 0; i < player->n_elements; i++)
    printf("%c ", player->data[i]);
}
