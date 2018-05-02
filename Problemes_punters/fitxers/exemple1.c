#include <stdio.h>

int main () {

   int  var = 20;   /* actual variable declaration */
   int  *ip;        /* pointer variable declaration */

   ip = &var;  /* store address of var in pointer variable*/

   printf("Address of var variable: %x\n", &var  );
   printf("Address stored in ip variable: %x\n", ip );
   printf("Value of *ip variable: %d\n", *ip );

   *ip = 30; /* Change value of the contents of *ip */
   printf("Value of variable var: %d\n", var);

   return 0;
}
