#include <stdio.h>
#include <stdlib.h>


int main(){
    char *filename = (char*)malloc(256*sizeof(char));
    if(filename == NULL){
        printf("Memory allocation error!\n");
        return 1;
    }
    printf("Enter the filename: ");
    scanf("%s", filename);
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    int width=512, height=512;
    int arr[height][width];
    int maxval;
    char P[3];
    char line[256];
    fscanf(fptr, "%2s", &P);
    fgetc(fptr);
    do{
        if(!fgets(line, sizeof(line), fptr)){
            return 1;
        }
        printf("line is: %s\n", line);
    } while(line[0] == '#');
    sscanf(line, "%u %u", &width, &height);
    fscanf(fptr, "%d", &maxval);
    printf("max value: %d\n", maxval);
    for(int i=0; i<height; i++){
        for(int j=0; j<width;j++){
            fscanf(fptr, "%d", &arr[i][j]);
        }
    }
    fclose(fptr);
    fptr = fopen("output.pgm", "w");
    fprintf(fptr, "%s\n", P);
    fprintf(fptr, "%d %d\n", width, height);
    fprintf(fptr, "%d\n", maxval);
    for(int i=0; i<height; i++){
        for(int j=0; j<width;j++){
            fprintf(fptr, "%d ", 255 - arr[i][j]);
        }
        fprintf(fptr, "\n");
    }
    fclose(fptr);
    return 0;
}