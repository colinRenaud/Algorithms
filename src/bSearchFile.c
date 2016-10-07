#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void bSearchFile(const char* path, const char c);

void generate_text(char* fileName,size_t size);

int main(int argc, char** argv) {
    if(argc != 3) {
        fprintf(stderr,"Error bad argument number"); exit(1);
    }
    if(! strlen(argv[1])) {
        fprintf(stderr,"Error first argument is null"); exit(2);
    }
    if(! strlen(argv[2])) {
        fprintf(stderr,"Error second argument is null"); exit(2);
    }
    bSearchFile(argv[1],argv[2][0]);
}

void bSearchFile(const char* path, const char c) {
    if(strlen(path) == 0 ) {
        fprintf(stderr,"Error path is null"); exit(3);
    }
    FILE* file = fopen(path,"r");
    if(file == NULL ) {
        perror("Couldn't open file"); exit(4);
    }
    if(fseek(file,0,SEEK_END)) {
        perror("Error when calling fseek to the end of file");exit(5);
    }
    intmax_t end = ftell(file) -1;
    if( end == 1L) {
        perror("Error when calling ftell to get size");exit(6);
    }
    if(fseek(file,0,SEEK_SET)) {
        perror("Error when calling fseek to the begin of file\""); exit(7);
    }
    intmax_t begin = 0;
    while(begin < end) {
        intmax_t middle= (begin+end)/2;
        if( fseek(file,middle,SEEK_SET)) {
            perror("Error when calling fseek to the middle of file");exit(8);
        }
        char buff = (char) fgetc(file);
        if(buff == EOF) {
            perror("End of file reading : EOF reached ");exit(9);
        }
        if(buff < c)
            begin = middle;
        else if( buff > c)
            end = middle;
        else {
            begin = end;
            printf("The character %c is at position %ld \n",c,middle+1);
        }
    }
    if (fclose(file) == EOF) {
        perror("Error when closing the file");exit(10);
    }
}
