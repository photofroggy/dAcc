/**
 * @file dAcc/map.h
 * @author Henry Rapley <photofroggy>
 * @version 1
 *
 * @section DESCRIPTION
 *
 * Header file defining the structs, types and functions relating to the
 * dAcc_map type.
 */


#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// dAcc_map data type.
typedef struct dAcc_map dAcc_map;

/**
 * Map data structure.
 * This data structure represents an entry in a map of key-value pairs. The
 * structure has a pointer to the next entry in the map, so a map entry object
 * also represents an entire map. Use the type `dAcc_map` for this.
 */
struct dAcc_map {
    char key[32];    //!< The key of the map entry.
    void *value;     //!< The value of the map entry.
    dAcc_map * next; //!< The next entry in the map.
};

// Map creation
dAcc_map* dAcc_map_empty();
dAcc_map* dAcc_map_new(char key[32], void * value);

// Map manipulation
int dAcc_map_append(dAcc_map * head, dAcc_map * map);
int dAcc_map_remove(dAcc_map * map, char key[32]);
int dAcc_map_set(dAcc_map * map, char key[32], void * value);

// Gets
void* dAcc_map_get(dAcc_map * map, char key[32]);
char* dAcc_map_gets(dAcc_map * map, char key[32]);
dAcc_map* dAcc_map_getm(dAcc_map * map, char key[32]);

// Map info
void dAcc_map_inspect(dAcc_map * map);
int dAcc_map_len(dAcc_map * map);
int dAcc_map_count(dAcc_map * map, void * value);

#ifdef __cplusplus
}
#endif

// EOF
