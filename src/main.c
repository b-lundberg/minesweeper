#include "textures.h"
#include "board.h"

/* FunctionsAndTypesNamedLikeThis are from raylib, as well
 * as some CONSTANTS_AND_MACROS */
#include <raylib.h>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

Texture TEXTURES[TEXTURE_COUNT];

#define CELL_SIZE 36

int main(void)
{
    board_t board = { .cols = 16, .rows = 20, .mines = 40 };
    srandom(clock());
    board_init(&board);
    board_open_all(&board);

    SetTraceLogLevel(LOG_WARNING);
    InitWindow(board.cols * CELL_SIZE, board.rows * CELL_SIZE, "MS");
    SetTargetFPS(60);

    for (enum texture_id id = 0; id < TEXTURE_COUNT; ++id) {
        TEXTURES[id] = LoadTexture(TEXTURE_PATHS[id]);
        if (!IsTextureValid(TEXTURES[id])) {
            TraceLog(LOG_ERROR,
                "Error: Failed to load texture '%s'\n", TEXTURE_PATHS[id]
            );
            return 1;
        }
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(0x00000000));
        for (int index = 0; index < BOARD_LENGTH(&board); ++index) {
            enum texture_id tid;
            cell_t cell = board.grid[index];
            switch (cell.state) {
            case CELL_STATE_FLAG:
                tid = TEXTURE_ID_flag;
                break;
            case CELL_STATE_CLOSED:
                tid = TEXTURE_ID_closed;
                break;
            case CELL_STATE_OPEN:
                if (cell.mine) {
                    tid = TEXTURE_ID_mine_blasted;
                    break;
                } else {
                    tid = (enum texture_id)cell.number;
                    break;
                }
            }
            DrawTexture(
                TEXTURES[tid],
                BOARD_I2X(&board, index) * CELL_SIZE,
                BOARD_I2Y(&board, index) * CELL_SIZE,
                GetColor(0xFFFFFFFF)
            );
        }
        EndDrawing();
    }
    CloseWindow();
}
