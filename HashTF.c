#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 10
#define N 10

// Estructura de un nodo de la linked list
struct Node {
    int key;
    int value;
    struct Node* next;
};

// Estructura de la tabla hash
struct HashTable {
    int size;
    struct Node** buckets;
    int* fnTable;  // Tabla de funciones aleatorias
};

// Prototipos de funciones
struct HashTable* createHashTable(int size);
void insert(struct HashTable* hashTable, int key, int value);
int find(struct HashTable* hashTable, int key);

// Función para crear una tabla hash
struct HashTable* createHashTable(int size) {
    struct HashTable* hashTable = (struct HashTable*)malloc(sizeof(struct HashTable));
    hashTable->size = size;
    hashTable->buckets = (struct Node**)malloc(sizeof(struct Node*) * size);

    // Inicializar los buckets con Vacío - NULL
    for (int i = 0; i < size; i++) {
        hashTable->buckets[i] = NULL;
    }

    // Inicializar la tabla de funciones aleatorias
    hashTable->fnTable = (int*)malloc(sizeof(int) * size);
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        hashTable->fnTable[i] = rand() % N;
    }

    return hashTable;
}

// Función para insertar un par (clave, valor)
void insert(struct HashTable* hashTable, int key, int value) {
    int index = hashTable->fnTable[key % hashTable->size];

    // Crear un nuevo nodo
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    // Si el bucket está vacío, simplemente inserta el nuevo nodo
    if (hashTable->buckets[index] == NULL) {
        hashTable->buckets[index] = newNode;
    } else {
        // Si hay alguien ocupando el espacio... añadiremos al principio de la linked list
        newNode->next = hashTable->buckets[index];
        hashTable->buckets[index] = newNode;
    }

    // Imprimir confirmación
    printf("Elemento (%d, %d) insertado con éxito. Función utilizada: %d\n", key, value, index);
}

// Función para buscar un valor dado una clave en la tabla hash
int find(struct HashTable* hashTable, int key) {
    int index = hashTable->fnTable[key % hashTable->size];

    // Buscar en la linked list con la correspondiente key
    struct Node* current = hashTable->buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            printf("Valor encontrado para la clave %d. Función utilizada: %d\n", key, index);
            return current->value;
        }
        current = current->next;
    }

    // Si la clave no se encuentra, retornar -1
    printf("Valor no encontrado para la clave %d. Función utilizada: %d\n", key, index);
    return -1;
}

// Función para imprimir la tabla hash completa
void printHashTable(struct HashTable* hashTable) {
    printf("Tabla Hash Completa:\n");
    for (int i = 0; i < hashTable->size; i++) {
        printf("Bucket %d (Función %d): ", i, hashTable->fnTable[i]);
        struct Node* current = hashTable->buckets[i];
        while (current != NULL) {
            printf("(%d, %d) ", current->key, current->value);
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    // Crear una tabla con M = 10
    struct HashTable* hashTable = createHashTable(M);

    // Insertar algunos elementos
    insert(hashTable, 123, 456);
    insert(hashTable, 789, 101);
    insert(hashTable, 567, 432);

    // Verificar que la tabla hash funciona
    printf("Value for key 123: %d\n", find(hashTable, 123));
    printf("Value for key 422: %d\n", find(hashTable, 422));
    printf("Value for key 567: %d\n", find(hashTable, 567));

    // Imprimir la tabla hash completa
    printHashTable(hashTable);

    // Liberar memoria
    free(hashTable->buckets);
    free(hashTable->fnTable);
    free(hashTable);

    return 0;
}

