#include <stdio.h>
#include <stdlib.h>

unsigned int loadRom(const char *rompath, unsigned char *buffer) {
    FILE *romfile;
    unsigned int filelen;

    romfile = fopen(rompath, "rb");
    if (!romfile) { return -1; }

    fseek(romfile, 0, SEEK_END);
    filelen = ftell(romfile);
    rewind(romfile);
    fread(buffer, filelen, 1, romfile);
    fclose(romfile);

    return filelen;
}

// Arguments:
//  argv[1] - path to rom file
int main(/* int argc, char** argv */) {
    unsigned char *instructions = malloc(0x2000000);

    printf("Loading ROM.\n");
    unsigned int programsize = loadRom("test/testrom.gb", instructions);
    if (programsize <= 1) { fprintf(stderr, "Failed to load ROM.\n"); return 1;}

    for (unsigned int i = 0; i < 650000; i++) {
        printf("%x", instructions[i]);
    }

    return 0;
}