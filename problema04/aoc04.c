#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

char * pass = "XMAS";

int main(int argc, char * argv[]){
    FILE* file;

    errno_t err = fopen_s(&file, argv[1], "r");

    // Buffer to store each line of the file.
    char chars[256][256];
    char line[256];

    // Check if the file was opened successfully.
    if (file && !err) {
        // Read each line from the file and store it in the
        // 'line' buffer.
        while (fgets(line, sizeof(line), file)) {
            int num_count = 0;
            int line_num = 0;
            int char_num = 0;

            printf("[LINE] %s", (char *)line);
            
            for(;;){
                // ret = strstr(&ret[char_num], "XMAS");
                chars[line_num][char_num] = line[char_num];
                if(!line[char_num])
                    break;
                char_num++;
            }
            printf("%s", chars[line_num]);
            line_num++;
        }

        while (1) {
            static int num_count = 0;
            static int line_num = 0;
            static int char_num = 0;

            printf("[LINE] %s", chars[line_num]);
            
            for(;;){
                // ret = strstr(&ret[char_num], "XMAS");
                if(chars[line_num][char_num] == 'X'){
                    printf("[CHAR] %c\n", chars[line_num][char_num]);
                }
                if(!line[char_num])
                    break;
                char_num++;
            }
            printf("%s\n", chars[line_num]);
            line_num++;
        }

        // Close the file stream once all lines have been
        // read.
        fclose(file);
    }
    else {
        // Print an error message to the standard error
        // stream if the file cannot be opened.
        fprintf(stderr, "Unable to open file!\n");
    }

    return 0;
}