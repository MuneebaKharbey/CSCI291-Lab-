#include<stdio.h> 
#include <stdbool.h> 
#define SIZE 24
#define Rows 8 //8
#define Cols 3//3


// PROTOTYPES
bool isValid(const int arr[],int length, int pos);
void remove_element(int arr[],int length, int pos);
void insert_element(int arr[], int length, int pos, int value);
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]);
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transpose[nCols][ nRows]);
bool found_duplicate(int arr[],int length);

int main()
{
   // Declaring variables
   int selection;
   int position;
   int value=80;
   
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 120, 121, 122, 123, 124};
    int length = sizeof(arr) / sizeof(arr[0]);

    printf("The original array is: \n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", arr[i]);
    }
   
   //Menu seleciton and call to associated functions
   printf("\n1. Remove element\n2. Insert element\n3. Reshape\n4. Transpose\n5. Check for duplicates \nEnter your choice: ");
   scanf("%d", &selection);
   if(selection==1){
      printf("Enter the position: ");
      scanf("%d",&position);
      if(isValid(arr, SIZE, position)){
         printf("Position is in the range\n");
          remove_element(arr,SIZE,position);
            for (int j=0; j<SIZE;j++){
            printf("%d ",arr[j]);
            }
         }else{
            printf("Wrong Value");
         }
   }  
   if (selection==2){
      printf("Enter the position: ");
      scanf("%d",&position);
      if(isValid(arr, SIZE, position)){
         printf("Position is in the range\n");
         insert_element( arr, SIZE, position, value);
         for(int j=0; j<SIZE;j++){
            printf("%d ",arr[j]);
         }
      }else{
            printf("Wrong Value");
         }
   }
  
   if(selection==3){   
      int arr2d[Rows][Cols];
      reshape(arr, SIZE,Rows,Cols,arr2d);
      for(int x=0; x<Rows; x++){
         for(int y=0;y<Cols;y++){
            printf("%d ",arr2d[x][y]);
         }
         printf("\n");
      }
   }

   if(selection==4){   
      int arr2d[Rows][Cols];
      int mat_transpose[Cols][Rows];
      // Calling reshape function to create the 2D array from the 1D array
      reshape(arr, SIZE,Rows,Cols,arr2d);
      // Calling function to create transpose
      trans_matrix(Rows, Cols, arr2d, mat_transpose);

      for(int f=0;f<Cols;f++){
         for(int b=0;b<Rows;b++){
            printf("%d ", mat_transpose[f][b]);
         }
      printf("\n");
      }
   }

   if(selection==5){
      bool duplicate=found_duplicate(arr,SIZE);
      printf("Array has duplicate: %s", duplicate ? "true" : "false");
   }
}



//FUNCTION DEFINITIONS
bool isValid(const int arr[],int length, int pos){
   if (pos>=0 && pos<length){
      return true;
   }else
   return false;
}

void remove_element(int arr[],int length, int pos){
   for(int i=pos ; i>0 ; i--){
      if (i<pos){
         arr[i]=arr[i-1];
      }
   }
}

void insert_element(int arr[], int length, int pos, int value){
   for(int i=0; i < pos; i++){
         arr[i] = arr[i + 1];
      }
      arr[pos - 1] = value;
}

void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]){
   if (length!=nRows * nCols){
      printf("Dimensions of 1D array do not match the 2D\n");
   }else{
      int l=0;
      for(int i= 0; i<nCols; i++){
         for(int k=0; k<nRows; k++){
            arr2d[k][i]= arr[l];
            l++;
         }
      }
   }
}

void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transpose[nCols][ nRows]){
   for(int i=0;i<nRows;i++){
      for(int j=0;j<nCols;j++){
         mat_transpose[j][i]=mat[i][j];
      }
   }
}

bool found_duplicate(int arr[],int length){
   for(int i=0;i<length;i++){
      for(int g=i+1;g<length;g++){
         if(arr[i]==arr[g]){
         return true;
         }
         else
         return false;
      }
   }  
}
