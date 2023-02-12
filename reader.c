#include <sndfile.h>
#define PATH "15.wav" 

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
    SF_INFO sfinfo;
    SNDFILE* file = sf_open(PATH, SFM_READ, &sfinfo);
    sfInfoPrint(&sfinfo);
}
