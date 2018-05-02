#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int final = 0;
int trans = 0;

struct Data {
    int* passenger_count;
    int* trip_time_in_secs;
    int total;
};

void consumer();
void producer(char*,int*, int, int);
struct Data* get_data(FILE*,int);
void send_consumer(struct Data*, int);
void finalizar(int signo);
void transferir(int signo);


int main(int argc, char *argv[])
{
	int pid;
	
	if(argc != 4)
	{
        printf("Hacen falta tres argumentos: %s <file> <num_consumers> <size_buffer>\n", argv[0]);
		exit(1);
	}
	
	char* filename = argv[1];
	int consumers = atoi(argv[2]);
	int lines = atoi(argv[3]);
	int pids[consumers];	

	/*
	 * TODO: Modificar (una vez funcione el resto) para crear mas de un consumidor
	 */
	int i;
    for(i=0; i<consumers; i++) {

        pid = fork();

        if(pid==0) {
            consumer();
        } else {
            pids[i] = pid;
        }
    }

    producer(filename,pids,consumers,lines);

    return 0;
}

void transferir(int signo){
    trans++;
}

void finalizar(int signo){
    final = 1;
}

void consumer()
{
	int fd;
	char filename[12];

    printf("Consumidor pid: %d\n", getpid());

    /*
     * TODO: preparar el codigo para recibir senyales del productor
     */
    signal(SIGUSR1,transferir);
    signal(SIGTERM, finalizar);
			
	// Abrimos un fichero con el nombre = pid para recibir los datos
	sprintf(filename, "%d", getpid());
	fd = open(filename, O_CREAT | O_RDWR | O_SYNC | O_APPEND , S_IRUSR | S_IWUSR | S_IRGRP);

	/*
	 *  TODO: Bucle para leer y procesar los datos del fichero que envia el productor
	 */
    int* passenger_count;
    int* trip_time_in_secs;
    int max, totalLinies = 0;
    float mean_passenger_count = 0.0, mean_trip_time = 0.0, partial_passenger_count, partial_trip_time;
    do {
        if (trans){
            trans--;
            read(fd, &max, sizeof(int));
            printf("Linies llegides consumidor %d: %d\n", getpid(), max);
            passenger_count = (int*)malloc(sizeof(int) * max);
            trip_time_in_secs = (int*)malloc(sizeof(int) * max);
            read(fd, passenger_count, sizeof(int) * max);
            read(fd, trip_time_in_secs, sizeof(int) * max);
            
            partial_passenger_count = 0.0;
            partial_trip_time = 0.0;
            
            for(int i=0; i<max; i++) {
                partial_passenger_count += (float) passenger_count[i];
                partial_trip_time += (float) trip_time_in_secs[i];
            }
            partial_passenger_count /= max;
            partial_trip_time /= max;
            
            mean_passenger_count = (mean_passenger_count*totalLinies + partial_passenger_count*max) / (totalLinies + max);
            mean_trip_time = (mean_trip_time*totalLinies + partial_trip_time*max) / (totalLinies + max);
            totalLinies += max;
            
            free(passenger_count);
            free(trip_time_in_secs);
        }
        
        if (trans == 0 && !final) {
            pause();
        }

    //Sortim quan: final i trans=0
    } while (!(final && (trans == 0)));
	
	close(fd);
	remove(filename);

	/*
 	 * TODO: Codigo para entregar resultado parcial al productor a traves del mismo fichero
     *       que se ha utilizado para recibir datos.
 	 */	
    
    printf("Total linies llegides consumidor %d: %d\n", getpid(), totalLinies);
    fd = open(filename, O_CREAT | O_RDWR | O_SYNC | O_APPEND , S_IRUSR | S_IWUSR | S_IRGRP);
    write(fd, &mean_passenger_count, sizeof(float));
    write(fd, &mean_trip_time, sizeof(float));
    write(fd, &totalLinies, sizeof(int));
    close(fd);
	exit(0);
}

void producer(char* filedata, int* pids, int total_consumers, int lines)
{
    FILE* file = fopen(filedata, "r");
    struct Data* d;
    char filename[12] = "";
    int i, fd;

    printf("Productor pid: %d\n",getpid());	

    i = 0;
    d = get_data(file,lines);
    while(d->total > 0)
    {		
        printf("Productor ha leido %d lineas\n", d->total);		
        send_consumer(d,pids[i]);

        /*
         * TODO: Codigo para notificar que hay datos a los consumidores (SIGUSR1)
         */			
        kill(pids[i], SIGUSR1);
        
        d = get_data(file,lines);

        i = (i+1)%total_consumers;
    }
    /*
     * TODO: Codigo para notificar que finalicen los consumidores (SIGTERM)
     */
    sleep(1); //Esperem que el consumidor processi la última senyal
    for (i=0; i < total_consumers; i++)
        kill(pids[i], SIGTERM);
    

    // Espera que los consumidores terminen
    for(i=0;i<total_consumers;i++)
        wait(NULL);

    float media_pasajeros = 0, media_tiempo_de_viaje = 0;
    int lineas = 0;

    /*
     * TODO: Leer resultados parciales de los consumidores y calcular valores finales.
     * Borrar el fichero filename al finalizar.
     */

    for(i=0; i<total_consumers; i++) {
        sprintf(filename, "%d", pids[i]);

        fd = open(filename, O_CREAT | O_RDWR | O_SYNC | O_APPEND , S_IRUSR | S_IWUSR | S_IRGRP);
        
        float media_parcial_pasajeros = 0.0, media_parcial_tiempo_de_viaje = 0.0;
        int lineas_parcial = 0;
        read(fd, &media_parcial_pasajeros, sizeof(float));
        read(fd, &media_parcial_tiempo_de_viaje, sizeof(float));
        read(fd, &lineas_parcial, sizeof(int));
        
        close(fd);
        remove(filename);

        media_pasajeros = (media_pasajeros*lineas + media_parcial_pasajeros*lineas_parcial) / (lineas + lineas_parcial);
        media_tiempo_de_viaje = (media_tiempo_de_viaje*lineas + media_parcial_tiempo_de_viaje*lineas_parcial) / (lineas + lineas_parcial);
        lineas += lineas_parcial;
    }

    printf("TOTAL de lineas leidas: %d\n", lineas);
    printf("Media de pasajeros: %f - Media de tiempo de viaje: %f \n",media_pasajeros,media_tiempo_de_viaje);
}

void send_consumer(struct Data* d, int consumer)
{
    int fd, data[2*(d->total)+1];
    char filename[12];
    sprintf(filename, "%d", consumer);
    fd = open(filename, O_CREAT | O_RDWR | O_SYNC | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP);

    /*
     * TODO: Codigo para enviar datos a consumidores. Se recomienda encarecidamente
     * que se utilitze un unico write para enviar los datos a un determinado consumidor.
     * Utilizar la variable 'data' para almacenar los datos en memoria antes de hacer
     * el write.
     */
    int i;
    data[0] = d->total;
    for(i = 0; i < d->total; i++){
        data[i+1] = d->passenger_count[i];
        data[d->total+i+1] = d->trip_time_in_secs[i];
    }
    write(fd, data, sizeof(int)*(2*(d->total)+1));
    close(fd);
}

int get_column_int(char* line, int num)
{
    char new_line[256];
    char* tok;
    int retvalue;

    strncpy(new_line, line, 256);
    for (tok = strtok(new_line, ",\n"); tok; tok = strtok(NULL, ",\n"))
    {
        if (!--num) {
            retvalue = (int) strtol(tok, (char **)NULL, 10);
            return retvalue;
        }
    }
    
    printf("ERROR: get_column_int\n");
    exit(1); 
}

struct Data* get_data(FILE* file, int max)
{
    struct Data *ret;
    char line[256];
    int pos = 0;
    char *c_passenger_count, *c_trip_time_in_secs;

    ret = (struct Data*)malloc(sizeof(struct Data));
    ret->passenger_count = (int*)malloc(sizeof(int) * max);
    ret->trip_time_in_secs = (int*)malloc(sizeof(int) * max);

    if(ftell(file) == 0)
        fgets(line, sizeof(line), file);

    while (pos < max && fgets(line, sizeof(line), file))
    {
        ret->passenger_count[pos] = get_column_int(line, 8);
        ret->trip_time_in_secs[pos] = get_column_int(line, 9); 
        pos++;
    }
    ret->total = pos;

    return ret;
}
