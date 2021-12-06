#ifndef _bmpReader
#define _bmpReader
#include "bmp.h"
#include <stdlib.h>
#include "image.h"

struct bmp_header 
{
        uint16_t signature;
        uint32_t fileSize;
        uint32_t reserved;
        uint32_t offset;
        uint32_t header_size;
        uint32_t width;
        uint32_t height;
        uint16_t planes;
        uint16_t bit_count;
        uint32_t compression;
        uint32_t image_size;
        uint32_t PPM_x;
        uint32_t PPM_Y;
        uint32_t colors_used;
        uint32_t colors_important;
};

enum read_status  {
  READ_OK = 0,
  READ_FAILED,
  READ_INVALID_SIGNATURE,
  READ_INVALID_BITS,
  READ_INVALID_HEADER,
  UNABLE_TO_CLOSE_FILE
  };

enum read_status from_bmp( FILE* in, struct image* img );

enum  write_status  {
  WRITE_OK = 0,
  WRITE_ERROR,
  UNABLE_TO_CLOSE_FILE
};

enum rotate_status {
  ROTATE_OK = 0,
  ROTATE_FAILED
}

enum write_status to_bmp( FILE* out, struct image const* img );
#endif