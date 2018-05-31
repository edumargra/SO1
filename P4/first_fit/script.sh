export LD_PRELOAD=
gcc exemple.c -o exemple
gcc -O -shared -fPIC malloc_first_fit.c -o malloc_first_fit.so
export LD_PRELOAD=/$PWD/malloc_first_fit.so

./exemple
