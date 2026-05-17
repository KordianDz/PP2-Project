#include "funkcje_universalne.h"

#include <ctype.h>

int porownaj_male_litery(char *slowo1, char *slowo2)
{
    int i = 0;
    while(slowo1[i] != '\0' && slowo2[i] != '\0')
    {
        if(tolower(slowo1[i]) != tolower(slowo2[i]))
        {
            return tolower(slowo1[i]) - tolower(slowo2[i]);
        }
        i++;
    }
    
    return tolower(slowo1[i]) - tolower(slowo2[i]);
}