#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{    
    char *str, *str1, *str2, *str3,*str4,*str5;

    str = malloc(5000 * sizeof(char));
    free(str);
    
    str1 = malloc(2000 * sizeof(char));
    str5 = realloc(str1, 3000);
    free(str5);

    str2 = malloc(sizeof(char)*1000);
    free(str2);

    str3 = calloc(sizeof(char), 4000);
    free(str3);
    
    
    str4 = malloc(2000 * sizeof(char));
    fprintf(stderr, "Direccio str: %x\n", str);
    fprintf(stderr, "Direccio str4: %x\n", str4);
    
    return 0;
}
