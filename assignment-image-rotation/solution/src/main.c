#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../../image/image.h"
#include "../../file/file_manager.h"
#include "../../rotate/rotate.h"

static const char* read_message[] = {
	[READ_OK] = "Данные прочитаны успешно!\n",
	[READ_FAILED] = "Не удалось прочитать данные!\n",
	[READ_INVALID_SIGNATURE] = "Ошибка чтения: Invalid signature\n",
	[READ_INVALID_BITS] = "Ошибка чтения: Invalid pixel data\n",
    [READ_INVALID_HEADER] = "Ошибка чтения: Invalid header\n",
    [UNABLE_TO_CLOSE_FILE] = "Не удалось закрыть файл!\n"
};

static const char* write_message[] = {
	[WRITE_OK] = "Данные успешно записаны!\n",
	[WRITE_ERROR] = "Ошибка при попытки записи в файл!\n",
	[UNABLE_TO_CLOSE_FILE] = "Не удалось закрыть файл!\n"
};

static const char* rotate_message[] = {
	[ROTATE_OK] = "Изображение успешно повернуто!\n",
	[ROTATE_FAILED] = "Произошла ошибка при попытки повернуть изображение!\n"
};

int main( int argc, char** argv ) {
	(void) argc; (void) argv;
    if (argc < 3) {
    	printf("%s\n", "Недостаточное количество параметров!");
    	return 0;
    }
    FILE* in = fopen(argv[0], "rb");
    FILE* out = fopen(argv[1], "ab");
    if (errno != 0) {
    	printf("%s\n", "Не удалось открыть файл для чтения!");
    	return 1;
    }
    if (errno != 0) {
    	printf("%s\n", "Не удалось открыть файл для записи!");
    	return 1;
    }
    struct image input_image = {0};
    struct image rotate_input_image = {0};
    const enum read_status = read_image_from_file(in, input_image);
    printf("%s\n", read_message[read_status]);
    if (read_status != READ_OK) return 0;
    const enum rotate_status = rotate(input_image, &rotate_input_image);
    printf("%s\n", rotate_message[read_status]);
    const enum write_status = write_image_to_file(out, rotate_input_image);
    printf("%s\n", write_message[write_status]);
    free(input_image.data);
    free(rotate_input_image.data);
    return 0;
}
