#include "board_renderer.h"

#include "board.h"
#include "textures.h"

#include <raylib.h>


static Rectangle cell_rect(board_renderer_t *renderer, int index)
{
    return (Rectangle) {
        BOARD_I2X(renderer->board, index) * renderer->render_size,
        BOARD_I2Y(renderer->board, index) * renderer->render_size,
        renderer->render_size,
        renderer->render_size
    };
}

bool board_renderer_init(board_renderer_t *renderer)
{
    renderer->canvas = LoadRenderTexture(
        renderer->board->cols * renderer->render_size,
        renderer->board->rows * renderer->render_size
    );
    SetTextureFilter(renderer->canvas.texture, TEXTURE_FILTER_BILINEAR);
    return IsRenderTextureValid(renderer->canvas);
}

void board_renderer_unload(board_renderer_t *renderer)
{
    UnloadRenderTexture(renderer->canvas);
}

void board_renderer_render(board_renderer_t *renderer)
{
    BeginTextureMode(renderer->canvas);
        for (int index = 0; index < BOARD_LENGTH(renderer->board); ++index) {
            Texture texture;
            cell_t cell = renderer->board->grid[index];
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
                (Rectangle) { 0, 0, texture.width, texture.height },
                cell_rect(renderer, index),
                (Vector2) { 0 }, 0, WHITE
            );
        }
    EndTextureMode();
}

void board_renderer_click(
    board_renderer_t *renderer,
    Vector2 pos,
    MouseButton btn
) {
    int index = 0;
    while (!CheckCollisionPointRec(pos, cell_rect(renderer, index))) {
        if (++index >= BOARD_LENGTH(renderer->board)) {
            return;
        }
    }
    if (btn == MOUSE_BUTTON_LEFT)
        board_open(renderer->board, index);
    else if (btn == MOUSE_BUTTON_RIGHT)
        board_flag(renderer->board, index);
    else if (btn == MOUSE_BUTTON_MIDDLE)
        board_open_around(renderer->board, index);
}
