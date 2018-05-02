#include <stdio.h>
#include <stdlib.h>

int main () {
   int *p_int;
   void  *ptr;
   
   ptr = malloc(4000);
   
   p_int = (int *) (ptr + 3);
   *p_int = 50;
   
   printf("Valor de ptr: %x\n", ptr);
   printf("Valor de p_int: %x\n", p_int);

   free(ptr);

   return 0;
} 
