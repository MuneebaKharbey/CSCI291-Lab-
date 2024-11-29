// Header files
#include <stdio.h>
#include <stdlib.h>

// Global constants
#define WIDTH 512 // Defines the width of the image
#define HEIGHT 512 // Defines the height of the image

// Function prototypes
int readPGMText(const char *filename, unsigned char *pixels, int width, int height);
int writePGMText(const char *filename, unsigned char *pixels, int width, int height);
int writePGMBinary(const char *filename, unsigned char *pixels, int width, int height);
void embedLSB(unsigned char *coverPixels, unsigned char *secretPixels, int width, int height);
void extractLSB(unsigned char *coverPixels, unsigned char *outputPixels, int width, int height);

int main() {
    char cover_image[] = "baboon.pgm"; // File name of the cover image
    char secret_image[] = "farm.pgm"; // File name of the secret image
    char stego_image[] = "stego_image_bin.pgm"; // Name of the output stego image
    char extracted_secret[] = "extracted_secret.pgm"; // Name for the extracted secret image

    unsigned char *coverPixels; // Pointer for the pixels of the cover image
    unsigned char *secretPixels; // Pointer for the pixels of the secret image
    unsigned char *outputPixels; // Pointer for the extracted secret image pixels

    int coverWidth = WIDTH; // Width of the cover image
    int coverHeight = HEIGHT; // Height of the cover image
    int secretWidth = WIDTH; // Width of the secret image
    int secretHeight = HEIGHT; // Height of the secret image

    // Dynamically allocate memory for the cover image pixels
    coverPixels = (unsigned char *)malloc(WIDTH * HEIGHT);
    if (coverPixels == NULL) {
        printf("Error: Memory allocation for coverPixels failed.\n");
        return 1;
    }

    // Load the cover image pixels
    if (readPGMText(cover_image, coverPixels, coverWidth, coverHeight) != 0) {
        printf("Error: Unable to read cover image.\n");
        free(coverPixels);
        return 1;
    }

    // Dynamically allocate memory for the secret image pixels
    secretPixels = (unsigned char *)malloc(WIDTH * HEIGHT);
    if (secretPixels == NULL) {
        printf("Error: Memory allocation for secretPixels failed.\n");
        free(coverPixels);
        return 1;
    }

    // Load the secret image pixels
    if (readPGMText(secret_image, secretPixels, secretWidth, secretHeight) != 0) {
        printf("Error: Unable to read secret image.\n");
        free(coverPixels);
        free(secretPixels);
        return 1;
    }

    // Check if dimensions of both images match
    if (coverWidth != secretWidth || coverHeight != secretHeight) {
        printf("Error: Image dimensions do not match.\n");
        free(coverPixels);
        free(secretPixels);
        return 1;
    }

    // Embed the secret image into the cover image using LSB
    embedLSB(coverPixels, secretPixels, WIDTH, HEIGHT);

    // Save the resulting stego image in binary format
    if (writePGMBinary(stego_image, coverPixels, WIDTH, HEIGHT) != 0) {
        printf("Error: Unable to save stego image.\n");
        free(coverPixels);
        free(secretPixels);
        return 1;
    }

    // Dynamically allocate memory for the output image (extracted secret)
    outputPixels = (unsigned char *)malloc(WIDTH * HEIGHT);
    if (outputPixels == NULL) {
        printf("Error: Memory allocation for outputPixels failed.\n");
        free(coverPixels);
        free(secretPixels);
        return 1;
    }

    // Extract the secret image from the stego image
    extractLSB(coverPixels, outputPixels, WIDTH, HEIGHT);

    // Save the extracted secret image
    if (writePGMText(extracted_secret, outputPixels, WIDTH, HEIGHT) != 0) {
        printf("Error: Unable to save extracted secret image.\n");
    }

    // Free dynamically allocated memory
    free(coverPixels);
    free(secretPixels);
    free(outputPixels);

    return 0;
}

// Function to read an ASCII PGM file
int readPGMText(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *file = fopen(filename, "r"); // Open the file for reading
    if (file == NULL) {
        return 1; // Return an error if file cannot be opened
    }

    char buffer[16];
    if (fgets(buffer, sizeof(buffer), file) == NULL || buffer[0] != 'P' || buffer[1] != '2') {
        fclose(file);
        return 1; // Return an error if the format is incorrect
    }

    // Skip any comments in the file
    do {
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            fclose(file); // Close the file if an error occurs
            return 1; // Return an error if reading fails
        }
    } while (buffer[0] == '#');

    int w;
    int h;
    int maxVal;
    sscanf(buffer, "%d %d", &w, &h); // Read width and height of the image
    if (fscanf(file, "%d", &maxVal) != 1 || w != width || h != height || maxVal != 255) {
        fclose(file); // Close the file if the image properties do not match
        return 1; // Return an error if the dimensions or max value do not match
    }

    // Read the pixel data
    for (int i = 0; i < width * height; i++) {
        if (fscanf(file, "%hhu", &pixels[i]) != 1) { // Read pixel values
            fclose(file); // Close the file if reading fails
            return 1; // Return an error if pixel data cannot be read
        }
    }

    fclose(file); // Close the file after reading
    return 0; // Successfully read the file
}

// Function to write an ASCII PGM file
int writePGMText(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *file = fopen(filename, "w"); // Open the file for writing
    if (file == NULL) {
        return 1; // Return an error if the file cannot be opened
    }

    fprintf(file, "P2\n# Created by stego_lsb.c\n%d %d\n255\n", width, height); // Write header

    // Write pixel data to the file
    for (int i = 0; i < width * height; i++) {
        fprintf(file, "%d\n", pixels[i]); // Write each pixel value
    }

    fclose(file); // Close the file after writing
    return 0; // Successfully written the file
}

// Function to write a binary PGM file
int writePGMBinary(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *file = fopen(filename, "wb"); // Open the file in binary write mode
    if (file == NULL) {
        return 1; // Return an error if the file cannot be opened
    }

    fprintf(file, "P5\n# Created by stego_lsb.c\n%d %d\n255\n", width, height); // Write header
    fwrite(pixels, sizeof(unsigned char), width * height, file); // Write pixel data in binary format

    fclose(file); // Close the file after writing
    return 0; // Successfully written the file
}

// Function to embed the secret image into the cover image using the LSB method
void embedLSB(unsigned char *coverPixels, unsigned char *secretPixels, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        coverPixels[i] = (coverPixels[i] / 16) * 16 + (secretPixels[i] / 16); // Embed the secret image into the cover image
    }
}

// Function to extract the secret image from the stego image using the LSB method
void extractLSB(unsigned char *coverPixels, unsigned char *outputPixels, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        outputPixels[i] = (coverPixels[i] % 16) * 16; // Extract the secret image from the stego image
    }
}
