#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;


/* //en hashmap.h
struct Pair {
    char * key;
    void * value;
};
*/


/*
La estructura HashMap cuenta con un arreglo de punteros 
Pair* (buckets). Cada Pair a su vez cuenta con dos variables: 
una clave (key) y el valor asociado (value). size corresponde 
a la cantidad de elementos que tiene el mapa y capacity es el 
tamaño actual del arreglo buckets.
*/
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

/*
Para poder ubicar datos dentro del arreglo, la tabla necesita 
dos funciones: la función hash (para transformar claves en 
posiciones) y la función is_equal (para comparar claves). En 
este laboratorio consideraremos que las claves son de tipo 
string (char*). Usaremos la siguiente función hash para 
transformar claves en posiciones dentro del arreglo:
*/
long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

/*
La función is_equal por su parte, simplemente debe indicar si 
dos claves son iguales (retorna 1) o no lo son (retorna 0):
*/
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

/*
Implemente la función void enlarge(HashMap * map). Esta función 
agranda la capacidad del arreglo buckets y reubica todos sus
 elementos. Para hacerlo es recomendable mantener referenciado 
 el arreglo actual/antiguo de la tabla con un puntero auxiliar. 
 Luego, los valores de la tabla se reinicializan con un nuevo 
 arreglo con el doble de capacidad. Por último los elementos 
 del arreglo antiguo se insertan en el mapa vacío con el método 
 insertMap. 
 
 Puede seguir los siguientes pasos:

a - Cree una variable auxiliar de tipo Pair** para matener el 
arreglo map->buckets (old_buckets);

b - Duplique el valor de la variable capacity.

c - Asigne a map->buckets un nuevo arreglo con la nueva capacidad.

d - Inicialice size a 0.

e - Inserte los elementos del arreglo old_buckets en el mapa 
(use la función insertMap que ya implementó).
*/
void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


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

/*
Implemente la función void eraseMap(HashMap * map, char * key). 
Está función elimina el dato correspondiente a la clave key. 
Para hacerlo debe buscar el dato y luego marcarlo para que no 
sea válido. No elimine el par, sólo invalídelo asignando NULL 
a la clave (pair->key=NULL). Recuerde actualizar la variable size.
*/
void eraseMap(HashMap * map,  char * key) {    
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

/*
Implemente las funciones para recorrer la estructura: 
Pair * firstMap(HashMap * map) retorna el primer Pair válido 
del arreglo buckets. 

Pair * nextMap(HashMap * map) retorna el siguiente Pair del 
arreglo buckets a partir índice current. Recuerde actualizar 
el índice.
*/
Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}


/*
Ya implementó todas las funcionalides del TDA Mapa.
Ahora ya puede comenzar a utilizar su mapa. Puede comenzar 
viendo el código de ejemplo del archivo main.c. Para compilar 
y ejecutar:
gcc main.c hashmap.c -o main; ./main
./main
Y voilá!
*/