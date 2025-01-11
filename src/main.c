#define TEXTURES_IMPL
#include "textures.h"
#include "board.h"

/* FunctionsAndTypesNamedLikeThis are from raylib, as well
 * as some CONSTANTS_AND_MACROS */
#include <raylib.h>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// actual size of textures is 36
#define CELL_SIZE 18

int main(void)
{
    board_t board = { .cols = 16, .rows = 16, .mines = 40 };
    srandom(clock());
    board_init(&board);
    board_open_all(&board);

    SetTraceLogLevel(LOG_WARNING);
    InitWindow(board.cols * CELL_SIZE, board.rows * CELL_SIZE, "MS");
    SetTargetFPS(60);

    // initializes TEXTURES
    if (!textures_load()) return 1;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        for (int index = 0; index < BOARD_LENGTH(&board); ++index) {
            Texture texture;
            cell_t cell = board.grid[index];
            switch (cell.state) {
            case CELL_STATE_FLAG:
                texture = TEXTURES[TEXTURE_ID_flag];
                break;
            case CELL_STATE_CLOSED:
                texture = TEXTURES[TEXTURE_ID_closed];
                break;
            case CELL_STATE_OPEN:
                if (cell.mine) {
                    texture = TEXTURES[TEXTURE_ID_mine_blasted];
                    break;
                } else {
                    texture = TEXTURES[(enum texture_id)cell.number];
                    break;
                }
            }
            DrawTexturePro(
                texture,
                // source
                (Rectangle) { 0, 0, texture.width, texture.height },
                // destination
                (Rectangle) {
                    BOARD_I2X(&board, index) * CELL_SIZE,
                    BOARD_I2Y(&board, index) * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE
                },
                // origin
                (Vector2) { 0 },
                // rotation
                0,
                // tint
                WHITE
            );
        }
        EndDrawing();
    }
    textures_unload();
    CloseWindow();
}
