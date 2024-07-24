#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h> // For ntohl
#include <errno.h>
#include <string.h>

uint32_t nbo(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        // 파일 열기에 실패했을 떄
        fprintf(stderr, "Error: Could not open file %s: %s\n", filename, strerror(errno));
        return 0;
    }

    uint32_t number;
    int lenth = fread(&number, sizeof(uint32_t), 1, file);
    fclose(file);

    if (lenth != 1) {
        // 파일에서 4바이트를 읽지 못했을 때
        fprintf(stderr, "Error: Could not read 4 bytes from file %s: %s\n", filename, strerror(errno));
        return 0;
    }

    return ntohl(number); 
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
	//파일 2개 안들어 왔을 때
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    uint32_t num1 = nbo(argv[1]);
    uint32_t num2 = nbo(argv[2]);

    uint32_t sum = num1 + num2;
    printf("%u (0x%x) + %u (0x%x) = %u (0x%x)\n", num1, num1, num2, num2, sum, sum);

    return 0;
}

