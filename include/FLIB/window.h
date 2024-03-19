#ifndef FLIB_WINDOW_H 
#define FLIB_WINDOW_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    const char *id;
    const char *title;
    uint32_t width;
    uint32_t height;
    bool visible;
    bool windowFrame;
} WindowSpec;

extern WindowSpec DEFAULT_WINDOW_SPEC;

#define WINDOW_SPEC_INITIALIZER DEFAULT_WINDOW_SPEC

#define FRAME_SPEC_VISIBLE_BIT
#define FRAME_SEC_FRAME_BIT

void window_create(WindowSpec spec);

#endif