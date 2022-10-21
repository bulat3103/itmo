#ifndef _FILE_MANAGER
#define _FILE_MANAGER

#include "../image/image.h"
#include "../bmp/bmp.h"
#include <stdio.h>

enum read_status read_image_from_file(FILE* in, struct image* const image);
enum write_status write_image_to_file(FILE* out, const struct image image);

#endif
