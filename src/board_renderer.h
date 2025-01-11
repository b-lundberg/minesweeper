#ifndef BOARD_RENDERER_H
#define BOARD_RENDERER_H

#include "board.h"

#include <raylib.h>


typedef struct board_renderer {
    board_t *board;
    int render_size;
    RenderTexture canvas;
} board_renderer_t;

bool board_renderer_init(board_renderer_t *renderer);
void board_renderer_unload(board_renderer_t *renderer);
void board_renderer_render(board_renderer_t *renderer);
void board_renderer_click(board_renderer_t *renderer,
                          Vector2 pos, MouseButton btn);

#endif // BOARD_RENDERER_H
