export LD_PRELOAD=
gcc exemple.c -o exemple
gcc -O -shared -fPIC malloc_best_fit_opcional.c -o malloc_best_fit_opcional.so
export LD_PRELOAD=/$PWD/malloc_best_fit_opcional.so
./exemple
