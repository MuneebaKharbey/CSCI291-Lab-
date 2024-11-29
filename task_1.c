// Include necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int invalidFloatCount = 0; // Counter for invalid data entries
    int validFloatCount = 0;   // Counter for valid floating-point numbers
    char wordBuffer[256];      // Buffer to store each word from the file

    const char *inputFileName = "data.txt";          // Input file to be read
    const char *outputFileName = "valid_data.txt";   // Output file to store valid data

    FILE *inputFile = fopen(inputFileName, "r");     // Open the input file in read mode
    FILE *outputFile = fopen(outputFileName, "w");   // Open (or create) the output file in write mode

    if (inputFile == NULL) {
        perror("Error opening input file"); // Error message if input file cannot be opened
        return 1;
    }

    if (outputFile == NULL) {
        perror("Error opening output file"); // Error message if output file cannot be opened
        fclose(inputFile); // Close input file
        return 1;
    }

    while (1) {
        long currentPosition = ftell(inputFile); // Store the current position in the input file

        if (fscanf(inputFile, "%255s", wordBuffer) == 1) {
            char *endPointer; // Pointer to check any remaining characters after conversion
            float floatValue = strtof(wordBuffer, &endPointer); // Convert word to float

            if (*endPointer == '\0') { // If the entire word is a valid float
                fprintf(outputFile, "%.2f\n", floatValue); // Write the valid float to the output file
                validFloatCount++; // Increment the valid float counter
            } else { // If the word is not a valid float
                fseek(inputFile, currentPosition + strlen(wordBuffer) + 1, SEEK_SET); // Move to the next word
                invalidFloatCount++; // Increment the invalid data counter
            }
        } else {
            if (feof(inputFile)) {
                break; // Exit loop if end of file is reached
            }
            if (ferror(inputFile)) {
                perror("Error reading input file"); // Error message if reading the file fails
                break; // Exit loop
            }
        }
    }

    fclose(inputFile);  // Close the input file
    fclose(outputFile);  // Close the output file

    printf("Total number of invalid float values: %d\n", invalidFloatCount); // Print invalid data count
    printf("Total number of valid float values: %d\n", validFloatCount);     // Print valid float count

    return 0;
}
