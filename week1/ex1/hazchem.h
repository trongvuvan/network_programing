#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct charone{
    int number;
    char chemystry_name[20];
}charone;

typedef struct chartwo{
    char type;
    bool colorIsWhite;
    char react;
    char protect[30];
    char contain[30];
}chartwo;

typedef struct charthree{
    char isE;
    char proceed[30];
}charthree;


void show();
void execute();

chartwo * findCharAndColor(chartwo secondtable[] ,char c,bool isColorWhite);