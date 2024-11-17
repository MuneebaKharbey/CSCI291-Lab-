#include<stdio.h> 
#include <stdbool.h> 

#define SIZE 24   // Define the size of the 1D array
#define Rows 8    // Number of rows for reshaping the array into a 2D matrix
#define Cols 3    // Number of columns for reshaping the array into a 2D matrix

// FUNCTION PROTOTYPES
bool isValid(const int arr[], int length, int pos); // Check if a position is valid within the array
void remove_element(int arr[], int length, int pos); // Remove an element at a given position
void insert_element(int arr[], int length, int pos, int value); // Insert a value at a specific position
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]); // Reshape a 1D array into a 2D matrix
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transpose[nCols][nRows]); // Transpose a matrix
bool found_duplicate(int arr[], int length); // Check for duplicate values in the array

int main() {
    // Declaring variables
    int selection; // User's menu selection
    int position;  // Position for insertion or deletion
    int value;     // Value to insert into the array
   
    int arr[SIZE] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 
                     130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240}; // Initialize array
    int length = sizeof(arr) / sizeof(arr[0]); // Calculate the array length

    // Print the original array
    printf("The original array is: \n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
   
    // Display menu options and get user's choice
    printf("\n1. Remove element\n2. Insert element\n3. Reshape\n4. Transpose\n5. Check for duplicates\nEnter your choice: ");
    scanf("%d", &selection);

    // Perform operations based on user's choice
    if (selection == 1) {
        // Remove an element
        printf("Enter the index position: ");
        scanf("%d", &position);

        if (isValid(arr, SIZE, position)) { // Check if position is valid
            printf("Position is in the range\n");

            remove_element(arr, SIZE, position); // Call remove_element function

            // Print the updated array
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", arr[j]);
            }
        } else {
            printf("Wrong Index Value"); // Invalid position
        }
    } else if (selection == 2) {
        // Insert an element
        printf("Enter the index position: ");
        scanf("%d", &position);

        printf("Enter the value: ");
        scanf("%d", &value);

        if (isValid(arr, SIZE, position)) { // Check if position is valid
            printf("Position is in the range\n");
            insert_element(arr, SIZE, position, value); // Call insert_element function

            // Print the updated array
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", arr[j]);
            }
        } else {
            printf("Wrong Index Value"); // Invalid position
        }
    } else if (selection == 3) {
        // Reshape the array into a 2D matrix
        int arr2d[Rows][Cols]; // Initialize a 2D array
        reshape(arr, SIZE, Rows, Cols, arr2d); // Call reshape function

        // Print the reshaped 2D array
        for (int x = 0; x < Rows; x++) {
            for (int y = 0; y < Cols; y++) {
                printf("%d ", arr2d[x][y]);
            }
            printf("\n");
        }
    } else if (selection == 4) {
        // Transpose a matrix
        int arr2d[Rows][Cols]; // Initialize the 2D array
        int mat_transpose[Cols][Rows]; // Initialize the transpose matrix

        reshape(arr, SIZE, Rows, Cols, arr2d); // Reshape array into 2D matrix
        trans_matrix(Rows, Cols, arr2d, mat_transpose); // Call trans_matrix function

        // Print the transposed matrix
        for (int f = 0; f < Cols; f++) {
            for (int b = 0; b < Rows; b++) {
                printf("%d ", mat_transpose[f][b]);
            }
            printf("\n");
        }
    } else if (selection == 5) {
        // Check for duplicates
        bool duplicate = found_duplicate(arr, SIZE);
        printf("Array has duplicate: %s", duplicate ? "true" : "false");
    }
}

// FUNCTION DEFINITIONS

// Check if a position is valid
bool isValid(const int arr[], int length, int pos) {
    return (pos >= 0 && pos < length);
}

// Remove an element from the array by shifting elements to the left
void remove_element(int arr[], int length, int pos) {
    for (int i = pos; i > 0; i--) {
        if (i < pos) {
            arr[i] = arr[i - 1];
        }
    }
}

// Insert an element into the array by shifting elements to the right
void insert_element(int arr[], int length, int pos, int value) {
    for (int i = 0; i < pos; i++) {
        arr[i] = arr[i + 1];
    }
    arr[pos - 1] = value;
}

// Reshape a 1D array into a 2D matrix
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]) {
    if (length != nRows * nCols) { // Check if dimensions match
        printf("Dimensions of 1D array do not match the 2D\n");
    } else {
        int l = 0;
        for (int i = 0; i < nCols; i++) {
            for (int k = 0; k < nRows; k++) {
                arr2d[k][i] = arr[l];
                l++;
            }
        }
    }
}

// Transpose a matrix
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transpose[nCols][nRows]) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            mat_transpose[j][i] = mat[i][j];
        }
    }
}

// Check for duplicate elements in the array
bool found_duplicate(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        for(int g = (i + 1); g < length; g++){
            if (arr[i] == arr[g]) {
                return true; // Duplicate found
            }
        }   
    }
    return false; // No duplicates
}
