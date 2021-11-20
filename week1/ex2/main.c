#include "subject.h"
#include "menu.h"
#include <stdio.h>


int main(int argc ,char* argv[]) {
    Subject *sub = NULL;

    if(argv[1] == NULL){
        printf("not found file");
    }

    readFileSubject(&sub, argv[1]);
    int opt;
    char loop;
    do{
        menu();
        scanf("%d", &opt);
        getchar();
        switch (opt)
        {
        case 1:
            addNewScoreBoard(&sub);
            printf("\n do you wanna back to the menu ? (y/n) ");
            scanf("%s",&loop);
            if(loop=='Y' || loop =='y')
            {
                continue;
            }
            else opt = 10;
            break;
        case 2:
            addScore(sub);
            printf("\n do you wanna back to the menu ? (y/n) ");
            scanf("%s",&loop);
            if(loop=='Y' || loop =='y')
            {
                continue;
            }
            else opt = 'J';
            break;
        case 3:
            removeScore(sub);
            printf("\n do you wanna back to the menu ? (y/n) ");
            scanf("%s",&loop);
            if(loop=='Y' || loop =='y')
            {
                continue;
            }
            else opt = 'Q';
            break;
        case 4:
            searchScore(sub);
            printf("\n do you wanna back to the menu ? (y/n) ");
            scanf("%s",&loop);
            if(loop=='Y' || loop =='y')
            {
                continue;
            }
            else opt = 'K';
            break;
        case 5:
            displayScore(sub);
            printf("\n do you wanna back to the menu ? y/n");
            scanf("%s",&loop);
            if(loop=='Y' || loop =='y')
            {
                continue;
            }
            else opt = 'A';
            break;
        default:
            break;
        }
    }while(opt < 6 || isalpha(opt) == 1);
    printf("\n___________________THE___________________END______________________\n");
    free(sub);
    return 0;
}