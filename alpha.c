#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define PATH "../wav/1.wav"
#define ALPHABET_SIZE 65536
#define BUFFER_SIZE 1024

typedef struct  _list{
    char cod;
    short value;
    int count;
    struct _list* right;
    struct _list* left;
}list;



int compare(const void *a, const void *b){
    return (*((list**)(a)))->count>(*((list**)(b)))->count;
}

void printLst(list* a){
    printf("cod:  %c\n", a->cod);
    printf("value:%hd\n",a->value);
    printf("count:%d\n",a->count);
    printf("right:%p\n",a->right);
    printf("left: %p\n",a->left);
}

void treeMaker(list* alph[]){
    for(int i = 0;i<ALPHABET_SIZE-1;i++){
        if (alph[i]->count==0) continue;

        list* lst = malloc(sizeof(list));
        *lst = (list){'0',0,alph[i]->count+alph[i+1]->count,alph[i],alph[i+1]};
        alph[i+1]->cod='1';
        alph[i+1]=lst;

        for(int j = i+1; j < ALPHABET_SIZE-1; j++){
            if(alph[j]->count<alph[j+1]->count) break;
            alph[j-1]=alph[j+1];
            alph[j+1]=alph[j];
            alph[j]=alph[j-1]; 
        }
    }
}

void printCod(char str[], int h){
    for(int i = 0; i<h;i++){
        printf("%c", str[i]);
    }
}

int printTree(list* tree, char str[], int h){
    str[h] = tree->cod;
    if (tree->left==NULL){
        printf("%d: K%d ", tree->count,h);
        printCod(str, h);
        printf("\n");
        str[h] = 0;
        return 0;
    }
    printTree(tree->left, str, h+1);
    printTree(tree->right, str, h+1);
    str[h] = 0;

}


int main(){

    list* alph[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++){
        alph[i] = malloc(sizeof(list));
        *alph[i] = (list){'0',i+SHRT_MIN,0,NULL,NULL};
    }
    printLst(alph[0]);

    short buffer[BUFFER_SIZE];
    //for (int i = 0; i < BUFFER_SIZE; i++, buffer[i] = 0);

    int counter = 0; 

    SF_INFO sfInfo;
    SNDFILE* file = sf_open(PATH, SFM_READ, &sfInfo); 

    
    while(counter = sf_read_short(file, buffer, BUFFER_SIZE)){
        for (int i = 0; i < counter; i++){
            alph[buffer[i]-SHRT_MIN]->count++;
        }
    }

    qsort(alph,ALPHABET_SIZE,sizeof(list*), compare);
    
    treeMaker(alph);
    char str[20];
    printTree(alph[ALPHABET_SIZE-1], str, 0);
    //printf("%d\n", alph[ALPHABET_SIZE-1]->count);

}

