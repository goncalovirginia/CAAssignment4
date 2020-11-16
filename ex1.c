 
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    char png[] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a}, fileBytes[24];
    fread(fileBytes, 1, 24, file);
    
    int width, height, *widthP = &width, *heightP = &height;
    
    if (memcmp(fileBytes, png, 8) == 0) {
        
        for (int i = 0; i < 4; i++) {
            *(widthP+i) = fileBytes[23-i];
            *(heightP+i) = fileBytes[19-i];
        }
        
        printf("PNG file: %d x %d\n", width, height);
    }
    else {
        printf("Not a PNG file.\n"); 
    }
    
    return 0;
}
