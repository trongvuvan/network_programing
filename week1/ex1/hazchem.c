#include "hazchem.h"

void execute()
{
    charone tableone[]={
        {1,"Jets"},
        {2,"Fog"},
        {3,"Foam"},
        {4,"Dry Agent"}
    };
    chartwo tabletwo[]={
        {'P', true, 'V', "Full", "Dilute"},
        {'R', true, ' ', "Full", "Dilute"},
        {'S', true, 'V', "BA", "Dilute"},
        {'S', false, 'V', "BA for fire only", "Dilute"},
        {'T', true, ' ', "BA", "Dilute"},
        {'T', false, ' ', "BA for fire only", "Dilute"},
        {'W', true, 'V', "Full", "Contain"},
        {'X', true, ' ', "Full", "Contain"},
        {'Y', true, 'V', "BA", "Contain"},
        {'Y', false, 'V', "BA for fire only", "Contain"},
        {'Z', true, 'V', "BA", "Contain"},
        {'Z', false, 'V', "BA for fire only", "Contain"}
    };
    char data_in[3];
    char color[15];
    bool isColorWhite = true;
    printf("Enter HAZCHEM code: ");
    scanf("%s",data_in);
    char charHasTowColor[4] = {'S', 'T', 'Y', 'Z'};
    for (int i = 0; i < 4; i++) {
        if (data_in[1] == charHasTowColor[i]) {
            printf("Is the %c reverse coloured : yes or no ? ", charHasTowColor[i]);
            scanf("%s", color);
            isColorWhite = (strcmp(color, "yes") == 0 ? false : true);
            break;
    }
    }

    if(findCharAndColor(tabletwo,data_in[1],isColorWhite))
    {
        chartwo result = *findCharAndColor(tabletwo,data_in[1],isColorWhite);
        printf("\n\n***Emergency action advice***\n");
        printf("Material:\t %s\n", tableone[(data_in[0] - '0') - 1].chemystry_name);
        if(result.react == 'V')
        {
            printf("Reactivity:\t %s\n","Can be violently reactive");
        }
        else printf("Reactivity:\t %s\n","");
        if(strcmp(result.protect, "Full") == 0)
        {
            printf("Protection:\t %s\n","Full protective clothing must be worn");
        }
        else printf("Protection:\t %s\n","Breathing apparatus, protective gloves for fire only");
        if(strcmp(result.contain, "Dilute") == 0 )
        {
            printf("Containment:\t %s\n","the dangerous goods may be washed down to a drain with a large quantity of water");
        }
        else printf("Containment:\t %s\n","A need to avoid spillages from entering drains or water courses");
        if (strlen(data_in) > 2) {
            printf("Evacuation:\t Consider evacuation\n");
            }
        printf("\n*****************************\n");
    }
    else printf("\n*****************************INPUT ERROR*****************************\n");

}

chartwo* findCharAndColor(chartwo secondtable[],char name,bool isColorWhite)
{
    for (int i = 0 ;i < 12;i++)
    {
        if(secondtable[i].type == name && secondtable[i].colorIsWhite == isColorWhite)
        {
            return &secondtable[i];
        }
    }
    return NULL;
}

