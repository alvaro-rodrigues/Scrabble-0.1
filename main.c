#include <stdio.h>
#include "game.h"
#include "player.h"
#include "bag.h"
#include "board.h"

int main(int argc, char const *argv[]) {

  int jump = 0;
  bag_t *bag = bagCreate();
  board_t *board = boardCreate(15, 15);
  player_t *player = playerCreate();
  player_t *player2 = playerCreate();
  game_t *game = gameCreate();
  playerAdd(game, player);
  playerAdd(game, player2);
  gameStart(game, bag);
  gameRound(game, game->first, game->first->player, bag, board, jump);

  return 0;
}
