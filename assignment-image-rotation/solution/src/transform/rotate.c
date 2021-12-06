#include "bmp.h"
#include "image.h"

enum rotate_status rotate(const struct image oldImage, struct image* const newImage) {
	size_t new_Width = oldImage.height;
	size_t new_Height = oldImage.width;
	*newImage = createImage(new_Width, new_Height);
	for (size_t i = 0; i < new_Height; i++) {
		for (size_t j = 0; j < new_Width; j++) {
			struct pixel pxl = oldImage.data[j * oldImage.width + i];
			*newImage.data[i * (*newImage.width) + (newImage->width - j - 1)] = pixel;
		}
	}
	return ROTATE_OK;
}