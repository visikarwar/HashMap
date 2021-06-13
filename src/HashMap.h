#define INIT_SIZE 16
#define PRIME_1 151
#define PRIME_2 23

typedef struct{
    char* key;
    char* value;
} entry;

typedef struct{
    int size;
    int count;
    entry** entries;
} hashmap;

hashmap* newHashMap();
void delHashMap(hashmap* hm);

void put(hashmap* hm, const char* key, const char* value);
char* get(hashmap* hm, const char* key);
void remove(hashmap* hm, const char* key);