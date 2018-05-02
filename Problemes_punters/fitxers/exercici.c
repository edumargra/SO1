#include <stdio.h>
#include <stdlib.h>

int main () {
   int i;
   void  *ptr;
   
   int var_int[1000];
   double var_double[1000];
   
   for(i = 0; i < 1000; i++) {
       var_int[i] = 2 * i + 1;
       var_double[i] = 2.5 * i + 6.7;
   }
   
   ptr = malloc(1000 * sizeof(int) + 1000 * sizeof(double));
   
   // Emmagatzemnar els valors de var_int i var_double
   // de forma intercalada. Primer var_int[0], seguit
   // de var_double[0], seguit de var_int[1], seguit
   // de var_double[1] i així successivament

   for(i = 0; i < 1000; i++) {
       *ptr = var_int[i];
       ptr++;
       *ptr = var_double[i];
       ptr++;
   }

   free(ptr);

   return 0;
} 
