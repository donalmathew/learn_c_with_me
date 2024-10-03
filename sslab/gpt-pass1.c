#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
    // File pointers for input, output symbol table, and operation table
    FILE *inputFile, *symbolTableFile, *operationTableFile;

    // Variables for location counter, starting address, and various operation parameters
    int locationCounter, startAddress, operandValue, operationCode, length;
    
    // Buffers for mnemonic, label, operand, and operation table mnemonic
    char mnemonic[20], label[20], operand[20], operationTableMnemonic[20];

    // Open input file in read mode
    inputFile = fopen("input.txt", "r");
    // Open symbol table file in write mode
    symbolTableFile = fopen("symtab.txt", "w");

    // Read the first line to check for START directive
    fscanf(inputFile, "%s %s %d", label, mnemonic, &operandValue);

    // If the first mnemonic is START, initialize starting address
    if (strcmp(mnemonic, "START") == 0) {
        startAddress = operandValue;
        locationCounter = startAddress;
        // Print the first line with starting address
        printf("\t%s\t%s\t%d\n", label, mnemonic, operandValue);
    } else {
        locationCounter = 0;
    }

    // Read the next label and mnemonic from the input file
    fscanf(inputFile, "%s %s", label, mnemonic);

    // Continue reading the input file until the end
    while (!feof(inputFile)) {
        // Read the operand
        fscanf(inputFile, "%s", operand);

        // Print the current line with the location counter
        printf("\n%d\t%s\t%s\t%s\n", locationCounter, label, mnemonic, operand);

        // If the label is not a placeholder, write it to the symbol table
        if (strcmp(label, "-") != 0) {
            fprintf(symbolTableFile, "\n%d\t%s\t%s\t%s\n", locationCounter, label, mnemonic, operand);
        }

        // Open the operation table file in read mode
        operationTableFile = fopen("optab.txt", "r");
        // Read the first mnemonic and operation code from the operation table
        fscanf(operationTableFile, "%s %d", operationTableMnemonic, &operationCode);

        // Search for the mnemonic in the operation table
        while (!feof(operationTableFile)) {
            if (strcmp(mnemonic, operationTableMnemonic) == 0) {
                // If found, increment location counter by 3 (assuming each instruction is 3 bytes)
                locationCounter += 3;
                break;
            }
            // Read the next mnemonic and operation code from the operation table
            fscanf(operationTableFile, "%s %d", operationTableMnemonic, &operationCode);
        }
        // Close the operation table file
        fclose(operationTableFile);

        // Handle different assembler directives
        if (strcmp(mnemonic, "WORD") == 0) {
            locationCounter += 3;  // WORD is 3 bytes
        } else if (strcmp(mnemonic, "RESW") == 0) {
            operandValue = atoi(operand);  // Convert operand to integer
            locationCounter += (3 * operandValue);  // RESW reserves 3 bytes for each word
        } else if (strcmp(mnemonic, "BYTE") == 0) {
            if (operand[0] == 'X') {
                locationCounter += 1;  // BYTE defined in hex is 1 byte
            } else {
                length = strlen(operand) - 3;  // BYTE defined in characters, calculate length
                locationCounter += length;  // Increment location counter by length
            }
        } else if (strcmp(mnemonic, "RESB") == 0) {
            operandValue = atoi(operand);  // Convert operand to integer
            locationCounter += operandValue;  // RESB reserves bytes as specified
        }

        // Read the next label and mnemonic from the input file
        fscanf(inputFile, "%s%s", label, mnemonic);
    }

    // If the last mnemonic is END, print the program length
    if (strcmp(mnemonic, "END") == 0) {
        printf("\nProgram Length = %d", locationCounter - startAddress);
    }

    // Close the input and symbol table files
    fclose(inputFile);
    fclose(symbolTableFile);
}
