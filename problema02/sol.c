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

int get_number_arrays_from_data(char * file_name, int num_lines){
    FILE * data_file;
    char buf[BUF_SIZE];

    data_file = fopen(file_name, "r");

    if (!data_file){
        printf("File not found or open\n");
    }
    else{
        printf("%p\n", data_file);
    }

    // for(int i = 0; i < num_lines; i++){

    //     fscanf(data_file, "%d %d", &left[i], &right[i]);

    //     printf("%d %d\n", left[i], right[i]);

    // }
    for(;;)
    {
        int counter = 0;
        size_t res = fread(buf, sizeof(int), BUF_SIZE, data_file);
        if (ferror(data_file) || res <= 0)
            return -1;

        printf("aqui %zu\n", res);

        for(int i = 0; i < res; i++){
            if (buf[i] == '\n'){
                printf("line break\n");
            }
            else if (buf[i] == ' '){
                counter++;
                printf("index %d\n", i);
            }
            // else if (feof(data_file)){
            //     // counter++;
            //     break;
            // }
            else{
                printf("%c\n", buf[i]);
                // printf("error\n");
            }
        }
    }
    // printf("Number of lines: %d\n", counter);

    fclose(data_file);

}

int main(int argc, char* argv[]){
    size_t file_num_of_lines;
    
    file_num_of_lines = count_lines_in_file(argv[1]);

    get_number_arrays_from_data(argv[1], file_num_of_lines);
    
    return 0;

}