#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>


typedef struct cell {
    char number; // 0-8
    bool mine;
    enum {
        CELL_STATE_CLOSED,
        CELL_STATE_OPEN,
        CELL_STATE_FLAG,
    } state;
} cell_t;

typedef struct board {
    int cols;
    int rows;
    int mines;
    cell_t *grid; // one-dimensional array of length cols*rows
} board_t;

#define BOARD_LENGTH(board) ((board)->cols * (board)->rows)

#define BOARD_I2X(board, index) ((index) % (board)->cols)
#define BOARD_I2Y(board, index) ((index) / (board)->cols)
#define BOARD_I2P(board, index) \
    BOARD_I2X(board, (index)),    \
    BOARD_I2Y(board, (index))
#define BOARD_P2I(board, x, y) ((board)->cols * (y) + (x))

void board_init(board_t *board);
void board_init_numbers(board_t *board);
void board_open(board_t *board, int index);
void board_open_all(board_t *board);

#endif // BOARD_H
