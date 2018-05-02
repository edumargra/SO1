#include <stdio.h>
#include <stdlib.h>

int main () {

   int  i, *var, *ptr;
   
   var = malloc(1000 * sizeof(int));
   ptr = var;

   for ( i = 0; i < 1000; i++) {
   		//var[i] = 2 * i + 1;
   		*ptr = 2 * i + 1;
   		printf("Value of *ptr for iteration %d is %x\n", i, *ptr);
   		ptr++;
   }
   
   free(var);
        
   return 0;
}
