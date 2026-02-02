#include "emulator.h"
#include <stdio.h>


unsigned int loadRom(const char *rompath, unsigned char instructions[]) {
    unsigned int bytesread = 0;
    unsigned int filesize = 0;
    
    FILE *romfile = fopen(rompath, "rb");
    
    if (!romfile) {
        fprintf(stderr, "Failed to load ROM.\n");
        return 0;
    }
    
    fseek(romfile, 0, SEEK_END);
    filesize = ftell(romfile);
    rewind(romfile);
    
    bytesread = fread(instructions, 1, filesize, romfile);
    
    if (bytesread != filesize) {
        fprintf(stderr, "Bytes read does not match the file size.\n");
        return 0;
    }
    
    fclose(romfile);
    
    return bytesread;
}

// Arguments:
//  argv[1] - path to rom file
int main(/* int argc, char** argv */) {
    unsigned char instructions[8192];

    printf("Loading ROM.\n");
    unsigned int programsize = loadRom("test/testrom.gb", instructions);
    if (programsize <= 0) { fprintf(stderr, "Failed to load ROM.\n"); return 1;}

    return 0;
}