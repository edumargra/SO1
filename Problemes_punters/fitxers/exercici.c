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
		*(int*)ptr = var_int[i];  //canviem el valor emmagatzemat a ptr
    printf("Value of var_int[%d] variable: %d\n", i, var_int[i] );
    printf("value stored in ptr variable: %d\n", *(int*)ptr );
    ptr = ptr + sizeof(int); //avancem el pointer per la mida d'un int

    *(double*)ptr = var_double[i]; //canviem el valor emmagatzemat a ptr
    printf("Value of var_double[%d] variable: %f\n", i, var_double[i] );
    printf("Value stored in ptr variable: %f\n", *(double*)ptr );
		ptr = ptr + sizeof(double); //avancem el pointer per la mida d'un double
	}

  //tornem a l'adreça de memòria inicial per alliberar correctament el punter
  ptr = ptr - (1000 * sizeof(int) + 1000 * sizeof(double));
	free(ptr);

	return 0;
}
