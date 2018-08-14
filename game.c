#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game.h"

game_t *gameCreate() {
  game_t *game = (game_t *) malloc(sizeof(game_t));
  if (game == NULL) {
    printf("Error, sem memória!!");
    exit(1);
  }
  game->first = NULL;
  game->last = NULL;
  game->num_elements = 0;
  return game;
}

void playerAdd(game_t *game, player_t *player) {
  node_t *new = (node_t *) malloc(sizeof(node_t));
  if (new == NULL) {
    printf("Error, sem memória!!");
    exit(1);
  }
  new->player = player;
  new->next = NULL;

  if (game->last != NULL)
  game->last->next = new;

  game->last = new;
  if (game->first == NULL)
  game->first = new;

  game->num_elements++;
  new->player->p_number = game->num_elements;
}

void gameStart(game_t *game, bag_t *bag) {
  bagFill(bag);
  node_t *toVisit = game->first;
  while (toVisit != NULL) {
    playerFill(toVisit->player, bag);
    toVisit = toVisit->next;
  }
}

void swap(int *values, int i, int j) {
  int aux = values[i];
  values[i] = values[j];
  values[j] = aux;
}

void insertion2(int *scores, int *players, int n) {
  for(int i = 1; i < n; i++)
    for(int j = i; j > 0; j--)
      if(scores[j-1] < scores[j]) {
        swap(scores, j-1, j);
        swap(players, j-1, j);
      }
}

void gameScoreBoard(game_t *game) {
  int players[game->num_elements];
  int scores[game->num_elements];
  char letters[] = {'A','B','C','D','E','F','G','H','I','J','L','M','N','O','P','Q','R','S','T','U','V','X','Z'};
  int values[] = {1, 3, 2, 2, 1, 4, 4, 4, 1, 5, 2, 1, 3, 1, 2, 1, 1, 1, 1, 1, 4, 8, 8};
  int j, k, m, i = 0;
  int add = 0;

  node_t *toVisit = game->first;
  while (toVisit != NULL) {
    players[i] = toVisit->player->p_number;
    scores[i] = toVisit->player->score;
    for (j = 0; j < MAX_SIZE; j++) {
      if (toVisit->player->data[j] != '\0') {
        for (k = 0; k < 23; k++) {
          if (toVisit->player->data[j] == letters[k]) {
            break;
          }
        }
        toVisit->player->score -= values[k];
        add +=values[k];
      }
    }
    i++;
    toVisit = toVisit->next;
  }

  toVisit = game->first;
  i = 0;
  while (toVisit != NULL) {
    int save = 1;
    for (m = 0; m < MAX_SIZE; m++) {
      if (toVisit->player->data[m] != '\0') {
        save = 0;
      }
    }
    if (save == 1) {
      toVisit->player->score += add;
    }
    players[i] = toVisit->player->p_number;
    scores[i] = toVisit->player->score;
    i++;
    toVisit = toVisit->next;
  }

  insertion2(scores, players, game->num_elements);
  printf("\tO jogador %d venceu!\n", players[0]);
  for (i = 0; i < game->num_elements; i++) {
    printf("\t%d - Jogador %d - %d Pontos\n", i+1, players[i], scores[i]);
  }
}

void gameRound(game_t *game, node_t *node, player_t *player, bag_t *bag, board_t *board, int jump) {
  int a, b, c, d, i, j;
  boardPrint(board);
  printf("\tJogador %d: ", player->p_number);
  playerPrint(player);
  printf("\t\tPontos: %d\n", player->score);
  printf("\t           0 1 2 3 4 5 6\n\n");
  printf("\t(1) Formar palavra\n\t(2) Trocar pedras\n\t(3) Passar a vez\n");
  printf("\tEscolha uma jogada: ");
  scanf("\t%d", &a);

  if (a == 1) {
    while (player->titles != 0) {
     if (jump > 0) {jump--;}
     printf("\tDigite o indice da letra a ser usada: ");
     scanf("%d", &b);
     printf("\tDigite a posição para inserir a letra (lin col): ");
     scanf("%d %d", &i, &j);
     printf("\n");
     boardInsert(board, i, j, player->data[b]);
     playerScore(player, player->data[b]);
     player->data[b] = '\0';
     player->titles--;
     if (player->titles != 0) {
       printf("\t(1) Colocar outra pedra\n\t(2) Terminar a jogada\n");
       printf("\tEscolha uma jogada: ");
       scanf("%d", &c);
       if (c == 2) {
         break;
       }
     } else {
       if (bag->head != NULL) {
         printf("\tVoce usou todas as suas pedras. Digite enter para passar a vez para o próximo jogador\n.");
         getchar();
         break;
       }
     }
    }
   playerRebuy(player, bag);
   if (player->titles == 0 && bag->head == NULL) {
     system("cls");
     boardPrint(board);
     printf("\tO jogador %d esgotou suas pedras e o saco esta vazio. Fim de jogo.\n", player->p_number);
     gameScoreBoard(game);
     exit(1);
   }
 }

 if (a == 2) {
   if (bag->head == NULL) {
     printf("\tSaco vazio. Pressione enter para tentar novamente");
     getchar();
     gameRound(game, node, player, bag, board, jump);
   } else {
   printf("\t(1) Trocar uma pedra\n\t(2) Trocar todas as pedras\n");
   printf("\tEscolha uma jogada: ");
   scanf("\t%d", &d);
   if (d == 1) {
     printf("\tDigite o indice da letra a ser trocada: ");
     scanf("%d", &b);
     bagInsert(bag, player->data[b]);
     player->data[b] = bagRemove(bag);
    }
   if (d == 2) {
     int m;
     for (m = 0; m < MAX_SIZE; m++) {
       if (player->data[m] != '\0') {
        bagInsert(bag, player->data[m]);
        player->data[m] = bagRemove(bag);
       }
     }
   }
 }
}

if (a == 3) {
  jump++;
  if (jump == 2) {
    system("cls");
    boardPrint(board);
    printf("\tOs dois jogadores pularam a vez. Fim de jogo.\n");
    gameScoreBoard(game);
    exit(1);
  }
}

 system("cls");
 node_t *nextPlayer;
 if (player == game->last->player) {
   nextPlayer = game->first;
 } else {
   nextPlayer = node->next;
 }
 gameRound(game, nextPlayer, nextPlayer->player, bag, board, jump);
}
