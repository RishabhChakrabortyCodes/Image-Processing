#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int width, height, maxval; char P[3];

int** readImage(){
    char *filename = (char*)malloc(256*sizeof(char));
    if(filename == NULL){
        printf("Memory allocation error!\n");
        return NULL;
    }
    printf("Enter the filename: ");
    scanf("%s", filename);
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        fclose(fptr);
        printf("Error opening file.\n");
        return NULL;
    }
    char line[256];
    fscanf(fptr, "%2s", &P);
    fgetc(fptr);
    do{
        if(!fgets(line, sizeof(line), fptr)){
            return NULL;
        }
        printf("line is: %s\n", line);
    } while(line[0] == '#');
    sscanf(line, "%u %u", &width, &height);
    int **arr = (int**)malloc(height*sizeof(int*));
    for(int i=0; i<height; i++){
        arr[i] = (int*)malloc(width*sizeof(int));
    }
    fscanf(fptr, "%d", &maxval);
    printf("max value: %d\n", maxval);
    for(int i=0; i<height; i++){
        for(int j=0; j<width;j++){
            fscanf(fptr, "%d", &arr[i][j]);
        }
    }
    fclose(fptr);
    return arr;
}

int writeImage(int** arr){
    FILE* fptr = fopen("output.pgm", "w");
    if (fptr == NULL) {
        printf("Error opening file.\n");
        fclose(fptr);
        return 1;
    }
    fprintf(fptr, "%s\n", P);
    fprintf(fptr, "%d %d\n", width, height);
    fprintf(fptr, "%d\n", maxval);
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            fprintf(fptr, "%d ", arr[i][j]);
        }
        fprintf(fptr, "\n");
    }
    fclose(fptr);
    return 0;
} 

int main(){
    int** img = readImage();
    int **arr = (int**)malloc(height*sizeof(int*));
    for(int i=0; i<height; i++){
        arr[i] = (int*)malloc(width*sizeof(int));
    }
    //Logic
    double gamma;
    printf("Enter the value of gamma:");
    scanf("%lf", &gamma);
    double c = (double)maxval/log(1+ (double)maxval);
    for(int i=0; i<height; i++){
        for(int j=0; j<width;j++){
            arr[i][j] = (int)((double)maxval*pow(((double)img[i][j]/(double)maxval), gamma));
        }
    }
    //End of Logic

    writeImage(arr);
    free(arr);
    return 0;
}