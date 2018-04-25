#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int finalitzar = 0;
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
void finalizar(void);
void transferir(void);


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
	consumers = 1; /* forzamos un consumidor */
	int pids[consumers];	
	
	pid = fork();

	/*
	 * TODO: Modificar (una vez funcione el resto) para crear mas de un consumidor
	 */
	
	if(pid==0) {
		consumer();
	}
	else
	{
		pids[0] = pid;
		producer(filename,pids,consumers,lines);
	}

    return 0;
}

void transferir(void){
    printf("He capturado la señal transferir.\n");
    trans = 1;
}

void finalizar(void){
    printf("He capturado la señal finalizar.\n");
    finalitzar = 1;
}

void consumer()
{
	int fd;
	char filename[12];

    printf("Consumidor pid: %d\n", getpid());

    /*
     * TODO: preparar el codigo para recibir senyales del productor
     */
    signal(SIGUSR1,trans);
    signal(SIGTERM, finalitzar);
			
	// Abrimos un fichero con el nombre = pid para recibir los datos
	sprintf(filename, "%d", getpid());
	fd = open(filename, O_CREAT | O_RDWR | O_SYNC | O_APPEND , S_IRUSR | S_IWUSR | S_IRGRP);

	/*
	 *  TODO: Bucle para leer y procesar los datos del fichero que envia el productor
	 */
    int* passenger_count, trip_time_in_secs;
    int max;
    float mean_passenger_count, mean_trip_time;
    
    while(!finalitzar){
        if (trans){
            trans = 0;
            read(fd, &max, sizeof(int));
            read(fd, passenger_count, sizeof(int) * max);
            read(fd, trip_time_in_secs, sizeof(int) * max);
            
            mean_passenger_count = (std::accumulate(passenger_count->begin(), passenger_count->end(), 0.0) / max + mean_passenger_count) / 2;
            mean_trip_time = (std::accumulate(trip_time_in_secs->begin(), trip_time_in_secs->end(), 0.0) / max + mean_trip_time) / 2;
        }
    }
	
	close(fd);
	remove(filename);

	/*
 	 * TODO: Codigo para entregar resultado parcial al productor a traves del mismo fichero
     *       que se ha utilizado para recibir datos.
 	 */	
    write(fd, &mean_passenger_count, sizeof(float));
    write(fd, &mean_trip_time, sizeof(float));
    
	exit(0);
}

void producer(char* filedata, int* pids, int total_consumers, int lines)
{
    FILE* file = fopen(filedata, "r");
    struct Data* d;
    char filename[12] = "";
    int i, fd;

    printf("Productor pid: %d\n",getpid());	

    d = get_data(file,lines);
    while(d->total > 0)
    {		
        printf("Productor ha leido %d lineas\n", d->total);		
        send_consumer(d,pids[0]);

        /*
         * TODO: Codigo para notificar que hay datos a los consumidores (SIGUSR1)
         */			
        kill(pids[0], SIGUSR1);
        
        d = get_data(file,lines);
    }

    /*
     * TODO: Codigo para notificar que finalicen los consumidores (SIGTERM)
     */
    kill(pids[0], SIGTERM);
    

    // Espera que los consumidores terminen
    for(i=0;i<total_consumers;i++)
        wait(NULL);

    float media_pasajeros = 0, media_tiempo_de_viaje = 0;
    int lineas = 0;

    sprintf(filename, "%d", pids[0]);

    /*
     * TODO: Leer resultados parciales de los consumidores y calcular valores finales.
     * Borrar el fichero filename al finalizar.
     */
    fd = open(filename, O_CREAT | O_RDWR | O_SYNC | O_APPEND , S_IRUSR | S_IWUSR | S_IRGRP);
    
    read(fd, &media_pasajeros, sizeof(float));
    read(fd, &media_tiempo_de_viaje, sizeof(float));
    
    close(fd);
    remove(filename);	

    printf("TOTAL de lineas leidas: %d\n", lineas);
    printf("Media de pasajeros: %f - Media de tiempo de viaje: %f \n",media_pasajeros,media_tiempo_de_viaje);
}

void send_consumer(struct Data* d, int consumer)
{
    int fd, data[2*d->total+1];
    char filename[12];
    sprintf(filename, "%d", consumer);
    fd = open(filename, O_CREAT | O_RDWR | O_SYNC | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP);

    /*
     * TODO: Codigo para enviar datos a consumidores. Se recomienda encarecidamente
     * que se utilitze un unico write para enviar los datos a un determinado consumidor.
     * Utilizar la variable 'data' para almacenar los datos en memoria antes de hacer
     * el write.
     */
    int i = 0;
    data[i] = d->total;
    for(i = 1; i < d->total; i++){
        data[i] = d->passenger_count[i];
        data[d->total+i] = d->trip_time_in_secs[i];
    }
    write(fd, data, sizeof(int)*2*(data->total)+1);
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
