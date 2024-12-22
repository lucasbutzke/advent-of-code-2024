#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 65536

size_t count_lines_in_file(char * file_name){
    FILE * data_file;
    char buf[BUF_SIZE];
    int counter = 0;

    data_file = fopen(file_name, "r");

    if (!data_file){
        printf("File not found or open");
    }
    else{
        printf("%p\n", data_file);
    }

    for(;;)
    {
        size_t res = fread(buf, 1, BUF_SIZE, data_file);
        if (ferror(data_file))
            return -1;

        int i;
        for(i = 0; i < res; i++)
            if (buf[i] == '\n')
                counter++;

        if (feof(data_file))
            counter++;
        
        break;
    }
    printf("Number of lines: %d\n", counter);
    
    fclose(data_file);

    return counter;
}

void get_number_arrays_from_data(char * file_name, int num_lines,
                                int * right, int * left){
    FILE * data_file;
    
    data_file = fopen(file_name, "r");

    if (!data_file){
        printf("File not found or open\n");
    }
    else{
        printf("%p\n", data_file);
    }

    for(int i = 0; i < num_lines; i++){

        fscanf(data_file, "%d %d", &left[i], &right[i]);

        printf("%d %d\n", left[i], right[i]);

    }

    fclose(data_file);

}

void sort_arrays(int num_lines, int * arr){
    int temp = 0;

    for (int first = 0; first < num_lines - 1; first++){
        for (int second = 0; second < num_lines - 1 - first; second++){
            if(arr[second] > arr[second+1]){
                temp = arr[second+1];
                arr[second+1] = arr[second];
                arr[second] = temp;
            }
            printf("%d\n", temp);
        }
        printf("\n");
    }
}

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main(int argc, char* argv[]){
    size_t file_num_of_lines;
    
    file_num_of_lines = count_lines_in_file(argv[1]);
    int left[file_num_of_lines];
    int right[file_num_of_lines];
    
    get_number_arrays_from_data(argv[1], file_num_of_lines, right, left);
    
    qsort(right, file_num_of_lines, sizeof(int), compare);
    qsort(left, file_num_of_lines, sizeof(int), compare);

    for (int t = 0; t < file_num_of_lines; t++){
        static int distance = 0;
        
        printf("%d %d\n", right[t], left[t]);

        distance += abs(left[t] - right[t]);
        printf("%d\n", distance);
    }

    for (int t = 0; t < file_num_of_lines; t++){
        int mul = 0;
        static int result = 0;
        printf("%d %d\n", right[t], left[t]);

        for (int m = 0; m < file_num_of_lines; m++){
            if(left[t] == right[m]){
                mul++;
            }
        }

        result += abs(left[t] * mul);
        printf("%d\n", result);
    }

    

    return 0;

}