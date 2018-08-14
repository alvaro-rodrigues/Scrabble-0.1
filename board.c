#include <stdlib.h>
#include <stdio.h>
#include "board.h"

board_t *boardCreate(int rows, int cols) {
	int i;
	board_t *board = (board_t *) malloc(sizeof(board_t*));
	if(board == NULL){
		printf("Erro, sem memória!!");
		exit(1);
	}
	board->cols = cols;
	board->rows = rows;
	board->data = (char **) malloc(rows * sizeof(char*));
	if(board->data == NULL){
		printf("Erro, sem memória!!");
		exit(1);
	}
	for(i = 0; i < rows; i++){
		board->data[i] = (char *) calloc(cols, sizeof(char));
		if(board->data[i] == NULL){
			printf("Erro, sem memória!!");
			exit(1);
		}
	}
	return board;
}

void boardPrint(board_t *board) {
	int rows, cols, i, j;
	rows = board->rows;
	cols = board->cols;
	for(i = 0; i < rows; i++){
		if(i == 0){
			for(j = 0; j < cols; j++){
				if(j == 0){
					printf("\t     ");
				}
				printf("%2d  ", j+1);
			}
			printf("\n");
			for(j = 0; j < cols; j++){
				if(j == 0){
					printf("\t    |");
				}
				printf("---|");
			}
			printf("\n");
		}
		for(j = 0; j < cols; j++){
			if(j == 0){
				printf("\t%2d  |", i+1);
			}
			if(board->data[i][j] == '?'){
				printf("   |");
			}
			else{
				printf(" %c |", board->data[i][j]);
			}
		}
		printf("\n");
		for(j = 0; j < cols; j++){
			if(j == 0){
				printf("\t    |");
			}
			printf("---|");
		}
		printf("\n");
	}
	printf("\n");
}

void boardInsert(board_t *board, int i, int j, char c) {
	board->data[i-1][j-1] = c;
}
