#define TEXTURES_IMPL
#include "textures.h"
#include "board.h"
#include "board_renderer.h"

/* FunctionsAndTypesNamedLikeThis are from raylib, as well
 * as some CONSTANTS_AND_MACROS */
#include <raylib.h>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define CELL_SIZE 36

Rectangle letterbox(Rectangle inner, Rectangle outer);

Vector2 rectproject(Vector2 point, Rectangle source, Rectangle dest);

Rectangle rectflip(Rectangle rect);

int main(void)
{
    board_t board = { .cols = 16, .rows = 16, .mines = 40 };
    srandom(clock());
    board_init(&board);

    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(600, 600, "MS");
    SetWindowMinSize(300, 300);
    SetTargetFPS(60);

    // initializes TEXTURES
    if (!textures_load()) return 1;

    board_renderer_t board_renderer = {
        .board = &board,
        .render_size = CELL_SIZE
    };
    if (!board_renderer_init(&board_renderer)) return 1;

    while (!WindowShouldClose()) {
        Rectangle screen_rect = {
            0.0f,
            0.0f,
            (float)GetScreenWidth(),
            (float)GetScreenHeight()
        };
        Rectangle board_rect = {
            0.0f,
            0.0f,
            (float)board_renderer.canvas.texture.width,
            (float)board_renderer.canvas.texture.height
        };
        Rectangle frame_rect = letterbox(
            board_rect,
            screen_rect
        );

        Vector2 screen_space_mouse = GetMousePosition();
        Vector2 world_space_mouse = rectproject(
            screen_space_mouse,
            frame_rect,
            board_rect
        );

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            board_renderer_click(&board_renderer,
                                 world_space_mouse,
                                 MOUSE_BUTTON_LEFT);
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            board_renderer_click(&board_renderer,
                                 world_space_mouse,
                                 MOUSE_BUTTON_RIGHT);
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
            board_renderer_click(&board_renderer,
                                 world_space_mouse,
                                 MOUSE_BUTTON_MIDDLE);
        }

        board_renderer_render(&board_renderer);
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(
                board_renderer.canvas.texture,
                rectflip(board_rect),
                frame_rect,
                (Vector2) { 0 }, 0, WHITE
            );
        EndDrawing();
    }
    board_renderer_unload(&board_renderer);
    textures_unload();
    CloseWindow();
}

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define ABS(x) MAX((x), -(x))

Rectangle letterbox(Rectangle inner, Rectangle outer)
{
    float scale = MIN(
        outer.width / inner.width,
        outer.height / inner.height
    );
    return (Rectangle) {
        0.5f * (outer.width - (inner.width * scale)),
        0.5f * (outer.height - (inner.height * scale)),
        inner.width * scale,
        inner.height * scale,
    };
}

Vector2 rectproject(Vector2 point, Rectangle source, Rectangle dest)
{
    return (Vector2) {
        dest.x + (point.x - source.x) * (dest.width / source.width),
        dest.y + (point.y - source.y) * (dest.height / source.height),
    };
}

Rectangle rectflip(Rectangle rect)
{
    rect.height *= -1;
    return rect;
}
