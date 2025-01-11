#include "board.h"

#include <stdlib.h>

#define NEIGHBOUR_ITER(board, this, nbor, body) do {   \
    int ax = BOARD_I2X((board), (this));               \
    int ay = BOARD_I2Y((board), (this));               \
    for (int dy = ay > 0 ? -1 : 0;                     \
         dy <= (ay >= (board)->rows - 1 ? 0 : 1);      \
         ++dy)                                         \
    for (int dx = ax > 0 ? -1 : 0;                     \
         dx <= (ax >= (board)->cols - 1 ? 0 : 1);      \
         ++dx)                                         \
    if (dx != 0 || dy != 0) {                          \
        nbor = BOARD_P2I((board), ax + dx, ay + dy);   \
        do body while (0);                             \
    }                                                  \
} while (0)

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

        NEIGHBOUR_ITER(board, index, int nbor, {
            cell->number += board->grid[nbor].mine;
        });
    }
}

void zero_open(board_t *board, int index)
{
    cell_t *cell = &board->grid[index];
    cell->visited = true;
    cell->state = CELL_STATE_OPEN;
    if (cell->number != 0) return;
    NEIGHBOUR_ITER(board, index, int nbor, {
        cell = &board->grid[nbor];
        if (!cell->visited && (cell->state == CELL_STATE_CLOSED))
            zero_open(board, nbor);
    });
}

bool board_open(board_t *board, int index)
{
    cell_t *cell = &board->grid[index];
    if (cell->state == CELL_STATE_CLOSED) {
        cell->state = CELL_STATE_OPEN;
        if (cell->mine) {
            return false;
        } else if (cell->number == 0) {
            for (int index = 0; index < BOARD_LENGTH(board); ++index)
                board->grid[index].visited = false;
            zero_open(board, index);
        }
    }
    return true;
}

void board_flag(board_t *board, int index)
{
    cell_t *cell = &board->grid[index];
    switch (cell->state) {
    case CELL_STATE_CLOSED: cell->state = CELL_STATE_FLAG;   break;
    case CELL_STATE_FLAG:   cell->state = CELL_STATE_CLOSED; break;
    case CELL_STATE_OPEN:                                    break;
    }
}

bool board_open_around(board_t *board, int index)
{
    if (board->grid[index].state != CELL_STATE_OPEN) return true;
    bool result = true;
    NEIGHBOUR_ITER(board, index, int nbor, {
        result = board_open(board, nbor) && result;
    });
    return result;
}

void board_open_all(board_t *board)
{
    for (int index = 0; index < BOARD_LENGTH(board); ++index)
        board_open(board, index);
}
