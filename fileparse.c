#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    BSKT = 0, KIDB, STRT, VRMM, NO_CHAIR
}chair;

const char* chair_names[] = {
    "Betriebssysteme + Kommunikationstechnologie",
    "Künstliche Intelligenz + Datenbanken",
    "Software + Robotik",
    "Virtuelle Realität + Multimedia",
    "kein Lehrstuhl angegeben"
};

typedef struct _worker{
    char last_name[24];
    char first_name[24];
    char title[24];
    unsigned int room_number;
    chair chair;
}worker;

chair get_chair(const char* chair_string){
    if(strncmp(chair_string, "BS/KT", 5) == 0){
        return BSKT;
    }
    if(strncmp(chair_string, "KI/DB", 5) == 0){
        return KIDB;
    }
    if(strncmp(chair_string, "ST/RT", 5) == 0){
        return STRT;
    }
    if(strncmp(chair_string, "VR/MM", 5) == 0){
        return VRMM;
    }
    return NO_CHAIR;
}

void print_workers_from_chair(worker* workers, size_t count, chair chair){

    printf("Lehrstuhl: %s\n", chair_names[chair]);
    
    for (size_t i = 0; i < count; i++){

        if (chair != workers[i].chair){
            continue;
        }

        printf("%s %s %s\n",
            workers[i].title,
            workers[i].first_name,
            workers[i].last_name
        );
    }
}

int main(void){

    FILE* file = fopen("fileparse.txt", "r");

    if (file == NULL){
        printf("Could not open file :( \n");
        return -1;
    }

    size_t lines;
    char ch;

    while(!feof(file)){
        ch = fgetc(file);
        if (ch == '\n'){
            lines++;
        }
    }

    rewind(file);

    printf("%zu lines in file.\n", lines);

    worker* workers = malloc(sizeof(worker) * lines);
    memset(workers, 0, sizeof(worker) * lines);

    char* line;
    size_t buf_len;
    size_t read;

    size_t count = 0;
    while( (read = getline(&line, &buf_len, file)) != -1 ){

        char delimiter[] = ",;";
        char* ptr = NULL;

        // read the last name
        ptr = strtok(line, delimiter);
        if(ptr != NULL){
            strncpy(workers[count].last_name, ptr, strlen(ptr));
        }else{
            printf("Could not read last name at line %zu\n", count+1);
            goto cleanup;
        }
        
        // read the first name
        ptr = strtok(NULL, delimiter);
        if(ptr != NULL){
            strncpy(workers[count].first_name, ptr, strlen(ptr));
        }else{
            printf("Could not read first name at line %zu\n", count+1);
            goto cleanup;
        }

        // read the title
        ptr = strtok(NULL, delimiter);
        if(ptr != NULL){
            strncpy(workers[count].title, ptr, strlen(ptr));
        }else{
            printf("Could not read title at line %zu\n", count+1);
            goto cleanup;
        }

        // read the room number
        ptr = strtok(NULL, delimiter);
        if(ptr != NULL){
            workers[count].room_number = atoi(ptr);
        }else{
            printf("Could not read room number at line %zu\n", count+1);
            goto cleanup;
        }

        // read the chair
        ptr = strtok(NULL, delimiter);
        if(ptr != NULL){
            workers[count].chair = get_chair(ptr);
        }else{
            printf("Could not read room number at line %zu\n", count+1);
            goto cleanup;
        }

        count++;
    }

    print_workers_from_chair(workers, lines, BSKT);

    cleanup:
    fclose(file);

    if(line != NULL){
        free(line);
    }

    free(workers);

    return 0;
}