#ifndef TEXTURES_H
#define TEXTURES_H

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

const char *TEXTURE_PATHS[TEXTURE_COUNT] = {
    #define X(name) "textures/" #name ".png",
    TEXTURE_LIST
    #undef X
};

#endif // TEXTURES_H
