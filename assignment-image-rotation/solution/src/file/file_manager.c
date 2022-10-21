#include "../../file/file_manager.h"
#include <stdio.h>
#include <errno.h>

enum read_status read_image_from_file(FILE* in, struct image* const image) {
	const enum read_status status = from_bmp(in, image);
	if (status != READ_OK) return status;
	fclose(in);
	if (errno !=0) return UNABLE_TO_CLOSE_FILE;
	return READ_OK;
}

enum write_status write_image_to_file(FILE* out, const struct image image) {
	const enum write_status status = to_bmp(out, image);
	if (status != WRITE_OK) return status;
	fclose(out);
	if (errno !=0) return UNABLE_TO_CLOSE_FILE;
	return WRITE_OK;
}