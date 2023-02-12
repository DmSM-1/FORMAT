#include <sndfile.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define PYCOMMAND "python3 graf.py<command.txt"

void sfInfoPrint(SF_INFO* sfinfo){

    printf("SF_INFO %p\n", sfinfo);
    if (sfinfo == NULL){
        printf(" NULL\n");
    }else{
        printf("frames     %ld\n", sfinfo->frames);
        printf("samplerate %d\n",  sfinfo->samplerate);
        printf("channels   %d\n",  sfinfo->channels);
        printf("format     %d\n",  sfinfo->format);
        printf("sections   %d\n",  sfinfo->sections);
        printf("seekable   %d\n",  sfinfo->seekable);
    }

}

void main(int argc, char* argv[]){

    if (argc!=3){
        printf("Error: wrong filename description");
        exit(1);
    }

    SF_INFO sfinfoIN;
    SNDFILE* fileIN = sf_open(argv[1], SFM_READ, &sfinfoIN);
    FILE* fp = fopen("data.txt", "w");

    sfInfoPrint(&sfinfoIN);
    double buffer[1024];
    int count = 0;
    
    for(int i = 0;(count = sf_read_double(fileIN, buffer, 1024));){
        for (int j = 0; j < count; j++){
            i++;
            fprintf(fp, "%d %lf\n",i, buffer[j]);
        }
    }

    fclose(fp);
    sf_close(fileIN);

    FILE* fc = fopen("command.txt", "w");
    fprintf(fc,"%s", argv[2]);
    fclose(fc);
    system(PYCOMMAND);
}
