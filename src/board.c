#include "board.h"

#include <stdlib.h>

void board_init(board_t *board)
{
    board->grid = malloc(sizeof(*board->grid) * BOARD_LENGTH(board));

    int mines_placed = 0;
    int index;
    bool *mine;
    while (mines_placed < board->mines) {
        // using modulo gives slightly biased results, idc
        index = random() % BOARD_LENGTH(board);
        mine = &board->grid[index].mine;
        if (!*mine) {
            *mine = true;
            ++mines_placed;
        };
    }
    if (mines_placed) board_init_numbers(board);
}

void board_init_numbers(board_t *board)
{
    for (int index = 0; index < BOARD_LENGTH(board); ++index) {
        cell_t *cell = &board->grid[index];

        if (cell->mine) continue;

        // mnemonics: absolute x/y, delta x/y
        int ax = BOARD_I2X(board, index);
        int ay = BOARD_I2Y(board, index);
        int dx, dy;

        /* I used dumb, stupid, undebuggable conditional operators to
         * handle board edges. My imagination told me that putting this
         * logic in the if-statement would be inefficient.
         * Whatever, it works now. */
        for (
            dy = ay > 0 ? -1 : 0;
            dy <= (ay >= board->rows - 1 ? 0 : 1);
            ++dy
        ) for (
            dx = ax > 0 ? -1 : 0;
            dx <= (ax >= board->cols - 1 ? 0 : 1);
            ++dx
        ) if (dx != 0 || dy != 0) {
            int other = BOARD_P2I(board, ax + dx, ay + dy);
            cell->number += board->grid[other].mine;
        }
    }
}

void board_open(board_t *board, int index)
{
    cell_t *cell = &board->grid[index];
    if (cell->state == CELL_STATE_CLOSED) cell->state = CELL_STATE_OPEN;
}

void board_open_all(board_t *board)
{
    for (int index = 0; index < BOARD_LENGTH(board); ++index)
        board_open(board, index);
}
