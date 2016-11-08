#include "process.h"
#include <malloc.h>
#include <string.h>

Process::Process(void *startMem) {
    numberOfPixel = 100;
    SharedMem *sharedMem = (SharedMem *)startMem;
    matrix = (unsigned char *)(startMem + sizeof(SharedMem));
    registers = (short int *)(matrix + numberOfPixel*numberOfPixel);
    flags = registers + 8;
    asmCommand = (AsmCommand *)(flags + 1);

    sharedMem->vidio_memory = matrix;
    sharedMem->registers = registers;
    sharedMem->flags = flags;
    sharedMem->asmCommand = asmCommand;

    strcpy(asmCommand[0].command, "HELLO: MOV    #MSG,R1");
    strcpy(asmCommand[1].command, "1$:    MOVB   (R1)+,R0");
    strcpy(asmCommand[2].command, "       BEQ    DONE");
    strcpy(asmCommand[3].command, "       .TTYOUT");
    strcpy(asmCommand[4].command, "       BR     1$");
    strcpy(asmCommand[5].command, "DONE:  .EXIT");
    strcpy(asmCommand[6].command, "MSG:   .ASCIZ /Hello, world!/");
    strcpy(asmCommand[7].command, "       .END    HELLO");

    for (int i = 0; i < numberOfCommand; i++)
        asmCommand[i].address = i+100;

    for (int i = 0; i < 8; i++)
        registers[i] = i+14;

    *flags = (short int)129;

    /*
    numberOfPixel = 100;
    matrix = (unsigned char **)calloc(sizeof(unsigned char *), numberOfPixel);
    if (!matrix) {
        printf("error with alloc memory\n");
        return;
    }
    for (int i = 0; i < numberOfPixel; i++) {
        matrix[i] = (unsigned char *)calloc(sizeof(unsigned char), numberOfPixel);
        if (!matrix[i]) {
            printf("error with alloc memory\n");
            return;
        }
    }

    int size_string = 100;
    numberOfCommand = 8;
    asmCommand = (AsmCommand *)malloc(sizeof(AsmCommand) * numberOfCommand);
    if (!asmCommand) {
        printf("error with alloc memory\n");
        return;
    }
    for (int i = 0; i < numberOfCommand; i++) {
        asmCommand[i].command = (char *)malloc(sizeof(char) * size_string);
        if (!asmCommand[i].command) {
            printf("error with alloc memory\n");
            return;
        }
    }

    strcpy(asmCommand[0].command, "HELLO: MOV    #MSG,R1");
    strcpy(asmCommand[1].command, "1$:    MOVB   (R1)+,R0");
    strcpy(asmCommand[2].command, "       BEQ    DONE");
    strcpy(asmCommand[3].command, "       .TTYOUT");
    strcpy(asmCommand[4].command, "       BR     1$");
    strcpy(asmCommand[5].command, "DONE:  .EXIT");
    strcpy(asmCommand[6].command, "MSG:   .ASCIZ /Hello, world!/");
    strcpy(asmCommand[7].command, "       .END    HELLO");

    for (int i = 0; i < numberOfCommand; i++)
        asmCommand[i].address = i+100;

    registers = (short int *)malloc(sizeof(short int) * 8);
    for (int i = 0; i < 8; i++)
        registers[i] = i+14;

    flags = new short int(129);
    */
}
/*
SharedMem Process::getGlobal() {
    Global myGlobal;
    myGlobal.asmCommand = asmCommand;
    myGlobal.flags = flags;
    myGlobal.registers = registers;
    myGlobal.vidio_memory = matrix;
    myGlobal.isFull = 1;

    //printf("global is set\n");
    printf("global: v_mem = %p, asmc = %p", myGlobal.vidio_memory, myGlobal.asmCommand);
    return myGlobal;
}
*/

/*
Process::~Process() {
    for (int i = 0; i < numberOfPixel; i++)
        free(matrix[i]);
    free(matrix);

    for (int i = 0; i < numberOfCommand; i++)
        free(asmCommand[i].command);
    free(asmCommand);
    free(registers);
    delete flags;
}
*/
void Process::run() {
    unsigned char c = 0;
    for (int x = 0; x < numberOfPixel; x++)
    for (int y = 0; y < numberOfPixel; y++) {
        matrix[x*numberOfPixel + y] = c++;
    }

}

void Process::stopReset() {
    for (int x = 0; x < numberOfPixel; x++)
    for (int y = 0; y < numberOfPixel; y++) {
        matrix[x*numberOfPixel + y] = 0;
    }
}


void Process::step() {

}
