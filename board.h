#ifndef BOARD_H
#define BOARD_H

typedef struct {
	int rows;
	int cols;
	char **data;
} board_t;

board_t *boardCreate(int rows, int cols);
void boardPrint(board_t *board);
void boardInsert(board_t *board, int i, int j, char c);

#endif
