#ifndef TEXTURES_H
#define TEXTURES_H

#include <raylib.h>

// https://en.wikipedia.org/wiki/X_macro
#define TEXTURE_LIST    \
    X(0)                \
    X(1)                \
    X(2)                \
    X(3)                \
    X(4)                \
    X(5)                \
    X(6)                \
    X(7)                \
    X(8)                \
    X(closed_hl_blue)   \
    X(closed_hl_green)  \
    X(closed_hl_red)    \
    X(closed_hl_yellow) \
    X(closed)           \
    X(flag)             \
    X(mine_blasted)     \
    X(mine)

enum texture_id {
    #define X(name) TEXTURE_ID_##name,
    TEXTURE_LIST
    #undef X
    TEXTURE_COUNT
};

#ifndef TEXTURES_IMPL

extern Texture TEXTURES[TEXTURE_COUNT];

#else // TEXTURES_IMPL

#include <stdbool.h>

const char *TEXTURE_PATHS[TEXTURE_COUNT] = {
    #define X(name) "textures/" #name ".png",
    TEXTURE_LIST
    #undef X
};

Texture TEXTURES[TEXTURE_COUNT];

bool textures_load()
{
    for (enum texture_id id = 0; id < TEXTURE_COUNT; ++id) {
        TEXTURES[id] = LoadTexture(TEXTURE_PATHS[id]);
        if (!IsTextureValid(TEXTURES[id])) {
            TraceLog(LOG_ERROR,
                "Error: Failed to load texture '%s'\n", TEXTURE_PATHS[id]
            );
            return false;
        }
    }
    return true;
}

void textures_unload()
{
    for (enum texture_id id = 0; id < TEXTURE_COUNT; ++id) {
        UnloadTexture(TEXTURES[id]);
    }
}

#undef TEXTURES_IMPL
#endif // TEXTURES_IMPL
#endif // TEXTURES_H
