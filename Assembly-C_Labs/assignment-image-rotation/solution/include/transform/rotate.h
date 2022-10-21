#ifndef _ROTATE
#define _ROTATE
#include "../bmp/bmp.h"
#include "../image/image.h"

enum rotate_status rotate(const struct image oldImage, struct image* const newImage);
#endif