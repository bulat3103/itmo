#ifndef _ROTATE
#define _ROTATE
#include "bmp.h"
#include "image.h"

enum rotate_status rotate(const struct image oldImage, struct image* const newImage);
#endif