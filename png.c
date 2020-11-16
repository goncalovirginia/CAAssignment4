
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    char png[] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a}, fileBytes[24];
    int width, height;
    
    fread(fileBytes, 1, 24, file);
    
    if (memcmp(fileBytes, png, 8) == 0) {
        char widthBytes[4], heightBytes[4];
        
        for (int i = 4; i > 0; i--) {
            widthBytes[i-1] = fileBytes[20-i];
            heightBytes[i-1] = fileBytes[24-i];
        }
        
        width = *((int*) widthBytes);
        height = *((int*) heightBytes);
        
        printf("PNG file: %d x %d\n", width, height);
    }
    else {
        printf("Not a PNG file.\n"); 
    }
    
    return 0;
}
