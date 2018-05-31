export LD_PRELOAD=
gcc exemple.c -o exemple
gcc -O -shared -fPIC malloc_best_fit.c -o malloc_best_fit.so
export LD_PRELOAD=/$PWD/malloc_best_fit.so
./exemple
