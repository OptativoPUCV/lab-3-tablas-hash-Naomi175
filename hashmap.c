#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void insertMap(HashMap * map, char * key, void * value) {
    long i = hash(key, map->capacity);
    long inicial_i = i;

    while (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
        if (is_equal(map->buckets[i]->key, key)) return;
        i = (i + 1) % map->capacity;
        if ( i == inicial_i) return;
    }

    map->buckets[i] = createPair(key, value);
    map->size++;
    map->current = i;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
    Pair ** old_buckets = map->buckets;
    long antiguo_i = map->capacity;

    map->capacity *= 2;
    map->buckets = (Pair **)calloc(map->capacity, sizeof(Pair *));
    map->size = 0;

    for (long i = 0 ; i < antiguo_i ; i++)
        if (old_buckets[i] != NULL && old_buckets[i]->key != NULL)
            insertMap(map, old_buckets[i]->key, old_buckets[i]->value);
    free(old_buckets);
}

HashMap * createMap(long capacity) {
    HashMap * map = (HashMap *)malloc(sizeof(HashMap));
    map->buckets = (Pair **)calloc(capacity, sizeof(Pair *));
    //map->buckets = (Pair **)malloc(capacity * sizeof(Pair *));
    //for (int i = 0; i < capacity; i++) { map->buckets[i] = NULL; }
    map->size = 0;
    map->capacity = capacity;
    map->current = -1;
    return map;
}

void eraseMap(HashMap * map,  char * key) {    
    long i = hash(key, map->capacity);
    long inicial_i = i;

    while (map->buckets[i] != NULL) {
        if (map->buckets[i]->key != NULL && is_equal(map->buckets[i]->key, key)) {
            map->buckets[i]->key = NULL;
            map->size--;
            return;
        }
        i = (i + 1) % map->capacity;
        if ( i == inicial_i) return;
    }
}

Pair * searchMap(HashMap * map,  char * key) {   
    long i = hash(key, map->capacity);
    long inicial_i = i;

    while (map->buckets[i] != NULL) {
        if (map->buckets[i]->key != NULL && is_equal(map->buckets[i]->key, key)) {
            map->current = i;
            return map->buckets[i];
        }
        i = (i + 1) % map->capacity;
        if ( i == inicial_i) return NULL;
    }
    return NULL;
}

Pair * firstMap(HashMap * map) {
    for (long i = 0 ; i < map->capacity ; i++) 
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
            map->current = i;
            return map->buckets[i];
        }
    return NULL;
}

Pair * nextMap(HashMap * map) {
    for (long i = map->current + 1 ; i < map->capacity ; i++)
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
            map->current = i;
            return map->buckets[i];
        }
    return NULL;
}