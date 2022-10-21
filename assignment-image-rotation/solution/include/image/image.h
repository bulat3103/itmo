#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"

struct image
{
  size_t width, height;
  struct pixel* data;
};

struct pixel
{
    uint8_t b, g, r;
};

struct image create_image(size_t width, size_t height);