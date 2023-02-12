#include <sndfile.h>
#include <stdint.h>
#include <stdlib.h>
#define PATHIN "output2.wav" 
#define PATHOUT "2.wav"

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

void main(){
    SF_INFO sfinfoIN;
    SNDFILE* fileIN = sf_open(PATHIN, SFM_READ, &sfinfoIN);
    FILE* fp = fopen("data.txt", "w");
    //SF_INFO sfinfoOUT = {sfinfoIN.frames, sfinfoIN.samplerate, sfinfoIN.channels, sfinfoIN.format, sfinfoIN.sections, sfinfoIN.seekable};
    //SNDFILE* fileOUT = sf_open(PATHOUT, SFM_WRITE, &sfinfoOUT);

    double buffer[1024];
    int count = 0;
    
    //printf("%d\n", sf_read_double(fileIN, &buffer, 1));
    for(int i = 0;(count = sf_read_double(fileIN, buffer, 1024));){
        for (int j = 0; j < count; j++){
            i++;
            fprintf(fp, "%d %lf\n",i, buffer[j]);
        }
        //printf("%d, %lf\n",reader,  buffer[0]);
    }

    fclose(fp);
    sf_close(fileIN);
    //sf_close(fileOUT);
}
