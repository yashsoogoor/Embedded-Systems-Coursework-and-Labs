#include "mbed.h"
#include "SDFileSystem.h"
using namespace std ;

SDFileSystem sd(p5, p6, p7, p8, "sd"); // the pinout on the mbed Cool Components workshop board

FILE * pFile;
long lSize;
char * buffer;
size_t result;

int main()
{
    printf("Hello World!\n");

    mkdir("/sd/mydir", 0777);

    FILE *fp = fopen("/sd/mydir/sdtest.txt", "w");
    if(fp == NULL) {
        error("Could not open file for write\n");
    }
    fprintf(fp, "Hello SD file world\n");
    fclose(fp);
    printf("file written\n");

    pFile = fopen ( "/sd/mydir/sdtest.txt" , "r" );
    if (pFile==NULL) {
        error ("File error");
    printf("file opened\n");
    }

    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {
        error ("Memory error");
    }

    // copy the file into the buffer:
    result = fread (buffer,1,lSize,pFile);
    if (result != lSize) {
        error ("Reading error");
        exit (3);
    }

    /* the whole file is now loaded in the memory buffer. */
    printf(buffer);

    // terminate
    fclose (pFile);
    free (buffer);

    printf("Finished!\n");
}
