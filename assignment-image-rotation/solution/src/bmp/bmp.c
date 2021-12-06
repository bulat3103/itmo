#include "bmp.h"
#include <stdlib.h>
#include "image.h"

enum read_status from_bmp( FILE* in, struct image* const img ) {
	struct bmp_header bmp_header= {0};
	enum read_status status = READ_FAILED;
	if (fread(&bmp_header, sizeof(struct bmp_header), 1, in)) {
		status = READ_OK;
	}
	if (status != READ_OK) return status;
	uint32_t width = bmp_header.width;
	uint32_t height = bmp_header.height;
	*img = create_image(width, height);
	const uint8_t offset = (width * 3) % 4;
	if (offset != 0) offset = 4 - offset;
	struct pixel* const pixels = (*img).data;
	for (uint32_t i = 0; i < height; i++) {
		if (fread(pixels + width * i, sizeof(struct pixel), width, in) != width || fseek(file, offset, SEEK_CUR) != 0) return READ_FAILED;
	}
	return READ_OK;
}

enum write_status to_bmp( FILE* out, struct image const* img ) {

}