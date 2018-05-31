#include <stdlib.h>
#include <stdio.h>

int main()
{
  int i;
  int *p;

  p = malloc(10000000 * sizeof(int)); //perk realment surti que esta buscant el millor progrmar un exemple sembla massa llarg, millor comprovar amb la compilacio del mateix exercici o un lexecucio dun programa
  

  for(i = 0; i < 10; i++)
    p[i] = i;

  for(i = 0; i < 10; i++)
    printf("%d\n", p[i]);
  
  p = calloc(10, sizeof(int));
  
  p = realloc(p,10 * sizeof(int));

  free(p);

  return 0;
}
