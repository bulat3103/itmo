#include "image.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdlib.h"

struct image create_image(size_t width, size_t height) 
{
    struct image newImage = {0};
    newImage.width = width;
    newImage.height = height;
    newImage.data = malloc(width * height * sizeof(struct pixel));
    return newImage;
}
