#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
    // File pointer to read from the file
    FILE *filePointer;
    
    // Variables to store various data
    int i, address, length, j, startAddress;
    char programName[10], line[50], objectProgramName[10], addressString[10], record[10], character, startAddressString[10];

    // Prompt the user to enter the program name
    printf("Enter Program Name: ");
    scanf("%s", programName);

    // Open the input file in read mode
    filePointer = fopen("ablinput.txt", "r");

    // Read the first line from the file
    fscanf(filePointer, "%s", line);

    // Extract the program name from the object program (starting from the 3rd character, length of 6 characters)
    for (i = 2, j = 0; i < 8 && j < 6; i++, j++)
        objectProgramName[j] = line[i];
    objectProgramName[j] = '\0';  // Null-terminate the string

    // Print the extracted program name
    printf("\nName from Obj. %s\n", objectProgramName);

    // Compare the entered program name with the name extracted from the object program
    if (strcmp(programName, objectProgramName) == 0) {
        do {
            // Read the next line from the file
            fscanf(filePointer, "%s", line);

            // If the line is a text record (starts with 'T')
            if (line[0] == 'T') {
                // Extract the starting address from the text record (starting from the 3rd character, length of 6 characters)
                for (i = 2, j = 0; i < 8 && j < 6; i++, j++)
                    startAddressString[j] = line[i];
                startAddressString[j] = '\0';  // Null-terminate the string

                // Convert the extracted starting address string to an integer
                startAddress = atoi(startAddressString);

                // Start processing the text record from the 13th character
                i = 12;
                while (line[i] != '$') {  // '$' is used as the end of the text record
                    if (line[i] != '^') {  // '^' is used as a delimiter in the record
                        // Print the address and corresponding object code
                        printf("00%d \t %c%c\n", startAddress, line[i], line[i + 1]);
                        startAddress++;  // Increment the address
                        i += 2;  // Move to the next pair of object code characters
                    } else {
                        i++;  // Skip the '^' character
                    }
                }
            }
            // If the line is an end record (starts with 'E')
            else if (line[0] == 'E') {
                // Do nothing (end of the object program)
            }
        } while (!feof(filePointer));  // Continue until the end of the file
    }
    
    // Close the file
    fclose(filePointer);
}
