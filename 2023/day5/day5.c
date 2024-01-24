#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>

#define LONG_MAXx 10000000
#define MAX 500

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

long seeds[LONG_MAXx];
long seed2soildest_range_start[MAX];
long seed2soilsource_range_start[MAX];
long seed2soilrange_length[MAX];
long soil2fertdest_range_start[MAX];
long soil2fertsource_range_start[MAX];
long soil2fertrange_length[MAX];
long fert2waterdest_range_start[MAX];
long fert2watersource_range_start[MAX];
long fert2waterrange_length[MAX];
long water2lightdest_range_start[MAX];
long water2lightsource_range_start[MAX];
long water2lightrange_length[MAX];
long light2tempdest_range_start[MAX];
long light2tempsource_range_start[MAX];
long light2temprange_length[MAX];
long temp2humiditydest_range_start[MAX];
long temp2humiditysource_range_start[MAX];
long temp2humidityrange_length[MAX];
long humidity2locdest_range_start[MAX];
long humidity2locsource_range_start[MAX];
long humidity2locrange_length[MAX];

//array of final locations
long final_locations[10];

struct arg_struct {
    long seedstart;
    long seedrange;
    int id;
};

void *compute_seeds(void *arguments) {

    struct arg_struct *args = arguments;
    long seedstart = args->seedstart;
    long seedrange = args->seedrange;
    int id = args->id;

    long *return_min = malloc(sizeof(long));
    long local_minimum = LONG_MAX;

    printf(ANSI_COLOR_RED "starting thread id : %d\n" ANSI_COLOR_RESET, id);
    printf(ANSI_COLOR_RED "seedstart = %ld\n" ANSI_COLOR_RESET, seedstart);
    printf(ANSI_COLOR_RED "seedrange = %ld\n" ANSI_COLOR_RESET, seedrange);

    for (long j = seedstart; j < seedstart + seedrange; j++) {

        long current_seed = j;

        //print the level of completion
        if (j == ((seedstart + seedrange) / 2)) {
            printf(ANSI_COLOR_RED "50% of thread id : %d\n" ANSI_COLOR_RESET, id);
        }

        for (long j = 0; j <= 2; j++) {
            long dest_range_start = seed2soildest_range_start[j];
            long source_range_start = seed2soilsource_range_start[j];
            long range_length = seed2soilrange_length[j];
            bool changed = false;

            if (current_seed >= source_range_start && current_seed < source_range_start + range_length) {
                long diff_to_start = current_seed - source_range_start;
                current_seed = dest_range_start + diff_to_start;
                //printf(ANSI_COLOR_GREEN " 1 soil seed changed to %ld\n" ANSI_COLOR_RESET, current_seed);
                changed = true;
            }

            if (changed) {
                break;
            }
        }

        //for in soil2fert depending on the size of the array
        for (long j = 0; j < 29; j++) {
            long dest_range_start = soil2fertdest_range_start[j];
            long source_range_start = soil2fertsource_range_start[j];
            long range_length = soil2fertrange_length[j];
            bool changed = false;

            if (current_seed >= source_range_start && current_seed < source_range_start + range_length) {
                long diff_to_start = current_seed - source_range_start;
                current_seed = dest_range_start + diff_to_start;
                //printf(ANSI_COLOR_GREEN "2 fert seed changed to %ld\n" ANSI_COLOR_RESET, current_seed);
                changed = true;
            }

            if (changed) {
                break;
            }
        }

        //for in fert2water depending on the size of the array
        for (long j = 0; j < 42; j++) {
            long dest_range_start = fert2waterdest_range_start[j];
            long source_range_start = fert2watersource_range_start[j];
            long range_length = fert2waterrange_length[j];
            bool changed = false;

            if (current_seed >= source_range_start && current_seed < source_range_start + range_length) {
                long diff_to_start = current_seed - source_range_start;
                current_seed = dest_range_start + diff_to_start;
                //printf(ANSI_COLOR_GREEN " 3 water seed changed to %ld\n" ANSI_COLOR_RESET, current_seed);
                changed = true;
            }

            if (changed) {
                break;
            }
        }

        //for in water2light depending on the size of the array
        for (long j = 0; j <= 40; j++) {
            long dest_range_start = water2lightdest_range_start[j];
            long source_range_start = water2lightsource_range_start[j];
            long range_length = water2lightrange_length[j];
            bool changed = false;

            if (current_seed >= source_range_start && current_seed < source_range_start + range_length) {
                long diff_to_start = current_seed - source_range_start;
                current_seed = dest_range_start + diff_to_start;
                //printf(ANSI_COLOR_GREEN " 4 light seed changed to %ld\n" ANSI_COLOR_RESET, current_seed);
                changed = true;
            }

            if (changed) {
                break;
            }
        }

        //for in light2temp depending on the size of the array
        for (long j = 0; j <= 30; j++) {
            long dest_range_start = light2tempdest_range_start[j];
            long source_range_start = light2tempsource_range_start[j];
            long range_length = light2temprange_length[j];
            bool changed = false;

            if (current_seed >= source_range_start && current_seed < source_range_start + range_length) {
                long diff_to_start = current_seed - source_range_start;
                current_seed = dest_range_start + diff_to_start;
                //printf(ANSI_COLOR_GREEN " 5 temp seed changed to %ld\n" ANSI_COLOR_RESET, current_seed);
                changed = true;
            }

            if (changed) {
                break;
            }
        }

        //for in temp2humidity depending on the size of the array
        for (long j = 0; j <= 46; j++) {
            long dest_range_start = temp2humiditydest_range_start[j];
            long source_range_start = temp2humiditysource_range_start[j];
            long range_length = temp2humidityrange_length[j];
            bool changed = false;

            if (current_seed >= source_range_start && current_seed < source_range_start + range_length) {
                long diff_to_start = current_seed - source_range_start;
                current_seed = dest_range_start + diff_to_start;
                //printf(ANSI_COLOR_GREEN " 6 humidity seed changed to %ld\n" ANSI_COLOR_RESET, current_seed);
                changed = true;
            }

            if (changed) {
                break;
            }
        }

        //for in humidity2loc depending on the size of the array
        for (long j = 0; j <= 40; j++) {
            long dest_range_start = humidity2locdest_range_start[j];
            long source_range_start = humidity2locsource_range_start[j];
            long range_length = humidity2locrange_length[j];
            bool changed = false;

            if (current_seed >= source_range_start && current_seed < source_range_start + range_length) {
                long diff_to_start = current_seed - source_range_start;
                current_seed = dest_range_start + diff_to_start;
                //printf(ANSI_COLOR_GREEN " 7 dest seed changed to %ld\n" ANSI_COLOR_RESET, current_seed);
                changed = true;
            }

            if (changed) {
                break;
            }
        }

        if (current_seed < local_minimum) {
            local_minimum = current_seed;
        }

    }

    return_min = &local_minimum;
    final_locations[id] = local_minimum;
    printf(ANSI_COLOR_RED "ending thread id : %d\n" ANSI_COLOR_RESET, id);
    printf(ANSI_COLOR_RED "local minimum = %ld\n" ANSI_COLOR_RESET, local_minimum);
    pthread_exit(return_min);

}

int main(int argc, char *argv[]) {


    //------------------[Check for correct usage]------------------//
    if (argc != 2) {
        printf("Usage: ./day2 <input file>\n");
        exit(1);
    }

    //------------------[Open input file]------------------//
    FILE *fptr;
    if ((fptr = fopen(argv[1], "r")) == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    char ligne[MAX];

    char **tokens = (char **)malloc(sizeof(char *) * 100);
        if (tokens == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }

    
    int ligneNum = 0;

    //------------------[Read input file]------------------//
    while (fgets(ligne, MAX, fptr)) {

        ligneNum++;

        ligne[strcspn(ligne, "\n")] = '\0';

        char *token = strtok(ligne, " ");
        int t = 0;

        while (token != NULL) {
            // Allouer de l'espace pour chaque token et le copier
            tokens[t] = (char *)malloc(strlen(token) + 1);

            // Vérifier si l'allocation a réussi
            if (tokens[t] == NULL) {
                fprintf(stderr, "Erreur d'allocation de mémoire.\n");
                exit(EXIT_FAILURE);
            }

            // Copier le token dans le tableau
            strcpy(tokens[t], token);

            // Incrémenter le compteur de tokens
            t++;

            token = strtok(NULL, " ");
        }

        if (ligneNum == 1) {
            for (int i = 0; i < 20; i++) {
                seeds[i] = atol(tokens[i + 1]);
            }

        }

        // parsing of the steps

        if (ligneNum >= 4 && ligneNum <= 6) {
            long dest_range_start = atol(tokens[0]);
            long source_range_start = atol(tokens[1]);
            long range_length = atol(tokens[2]);

            seed2soildest_range_start[ligneNum - 4] = dest_range_start;
            seed2soilsource_range_start[ligneNum - 4] = source_range_start;
            seed2soilrange_length[ligneNum - 4] = range_length;
        }

        if (ligneNum >= 9 && ligneNum <= 37) {
            long dest_range_start = atol(tokens[0]);
            long source_range_start = atol(tokens[1]);
            long range_length = atol(tokens[2]);

            soil2fertdest_range_start[ligneNum - 9] = dest_range_start;
            soil2fertsource_range_start[ligneNum - 9] = source_range_start;
            soil2fertrange_length[ligneNum - 9] = range_length;
        }

        if (ligneNum >= 40 && ligneNum <= 82) {
            long dest_range_start = atol(tokens[0]);
            long source_range_start = atol(tokens[1]);
            long range_length = atol(tokens[2]);

            fert2waterdest_range_start[ligneNum - 40] = dest_range_start;
            fert2watersource_range_start[ligneNum - 40] = source_range_start;
            fert2waterrange_length[ligneNum - 40] = range_length;
        }

        if (ligneNum >= 85 && ligneNum <= 125) {
            long dest_range_start = atol(tokens[0]);
            long source_range_start = atol(tokens[1]);
            long range_length = atol(tokens[2]);

            water2lightdest_range_start[ligneNum - 85] = dest_range_start;
            water2lightsource_range_start[ligneNum - 85] = source_range_start;
            water2lightrange_length[ligneNum - 85] = range_length;
        }

        if (ligneNum >= 128 && ligneNum <= 158) {
            long dest_range_start = atol(tokens[0]);
            long source_range_start = atol(tokens[1]);
            long range_length = atol(tokens[2]);

            light2tempdest_range_start[ligneNum - 128] = dest_range_start;
            light2tempsource_range_start[ligneNum - 128] = source_range_start;
            light2temprange_length[ligneNum - 128] = range_length;
        }

        if (ligneNum >= 161 && ligneNum <= 207) {
            long dest_range_start = atol(tokens[0]);
            long source_range_start = atol(tokens[1]);
            long range_length = atol(tokens[2]);

            temp2humiditydest_range_start[ligneNum - 161] = dest_range_start;
            temp2humiditysource_range_start[ligneNum - 161] = source_range_start;
            temp2humidityrange_length[ligneNum - 161] = range_length;
        }

        if (ligneNum >= 210 && ligneNum <= 250) {
            long dest_range_start = atol(tokens[0]);
            long source_range_start = atol(tokens[1]);
            long range_length = atol(tokens[2]);

            humidity2locdest_range_start[ligneNum - 210] = dest_range_start;
            humidity2locsource_range_start[ligneNum - 210] = source_range_start;
            humidity2locrange_length[ligneNum - 210] = range_length;
        }

    }

    long minimum = LONG_MAX;

    pthread_t threads[10];
    int rc;
    long t;
    void *thread_result;
    // array of args 
    struct arg_struct args[10];

    //fill this arrau 
    for (int i = 0; i < 10; i++) {
        args[i].seedstart = seeds[i*2];
        args[i].seedrange = seeds[i*2 + 1];
        args[i].id = i;
    }
    


    for (t = 0; t < 10; t++) {
        printf("In main: creating thread %ld\n", t);

        rc = pthread_create(&threads[t], NULL, compute_seeds, (void *)&args[t]);
        printf("thread with id %d created\n", t);

        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }

    }

    for (t = 0; t < 10; t++) {

        rc = pthread_join(threads[t], &thread_result);

        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    } 

    //compute the minimum of the array of final locations
    minimum = LONG_MAX;
    for (int i = 0; i < 10; i++) {
        if (final_locations[i] < minimum) {
            minimum = final_locations[i];
        }
    }

    //print final locations 
    for (int i = 0; i < 10; i++) {
        printf(ANSI_COLOR_GREEN"final location %d = %ld\n" ANSI_COLOR_RESET, i, final_locations[i]);
    }

    printf(ANSI_COLOR_CYAN"smallest location = %ld\n" ANSI_COLOR_RESET, minimum);
    

}