#include <stdlib.h>
#include <string.h>

#include "HashMap.h"

static entry* newEntry(char* k, char* v){
    entry* item = malloc(sizeof(entry));
    item->key = k;
    item->value = v;
    return item;
}

hashmap* newHashMap(){
    hashmap* map = malloc(sizeof(hashmap));
    map->size = INIT_SIZE;
    map->count = 0;
    map->entries = calloc((size_t)map->size, sizeof(entry));
    return map;
}

static void delEntry(entry* e){
    free(e->key);
    free(e->value);
    free(e);
}

void delHashMap(hashmap* hm){
    for(int i = 0; i<hm->size; i++){
        entry* item = hm->entries[i];
        if(item != NULL){
            delEntry(item);
        }
    }
    free(hm->entries);
    free(hm);
}

static int hash(const char* key, const int primeNum, const int modulo){
    long hash = 0;
    const int keyLength = strlen(key);
    for(int i = 0; i<keyLength; i++){
        hash += (long)pow(primeNum, keyLength - (i+1)) * key[i];
        hash = hash % modulo;
    }
    return (int)hash;
}

static int getIndex(const char* key, const int buckets, const int attempt){
    const int firstHash = hash(key, PRIME_1, buckets);
    const int secondHash = hash(key, PRIME_2, buckets);
    return (firstHash + attempt*(secondHash+1)) % buckets;
}

void put(hashmap* hm, const char* key, const char* value){
    entry* item = newEntry(key, value);
    int index = getIndex(key, hm->size, 0);
    entry* currentEntry = hm->entries[index];
    int attempt = 1;
    while(currentEntry!=NULL){
        index = getIndex(key, hm->size, attempt++);
        currentEntry = hm->entries[index];
    }
    hm->entries[index] = item;
    hm->count++;
}

char* get(hashmap* hm, const char* key){
    int attempt = 0;
    int index = getIndex(key, hm->size, attempt++);
    entry* currentEntry = hm->entries[index];

    while(currentEntry != NULL){
        if(strcmp(currentEntry->key, key) == 0){
            return currentEntry->value;
        }

        index = getIndex(key, hm->size, attempt++);
        currentEntry = hm->entries[index];
    }
    return NULL;
}

