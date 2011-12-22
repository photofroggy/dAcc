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

/* type: dAcc_map
 * members:
 *  - key (string)
 *  - value (pointer)
 *  - next (dAcc_map)
 *
 * This data type is supposed to be similar to a linked list
 * and hash map. We may be using these for packet arguments
 * later on in the lib.
 */
typedef struct _dAcc_map {
    char key[32];
    void *value;
    struct _dAcc_map * next;
} dAcc_map;

// Map creation
dAcc_map* dAcc_map_empty();
dAcc_map* dAcc_map_new(char key[32], void * value);

/* Map manipulation
 * These functions are concerned with manipulating maps
 * with regards to adding, removing and changing items in
 * map. These functions return an integer, 1 for failure, 0
 * for success.
 */
/// Add item: k-v, map
//int dAcc_map_add(dAcc_map * map, char key[32], void * value);
int dAcc_map_append(dAcc_map * head, dAcc_map * map);
/// Remove item
int dAcc_map_remove(dAcc_map * map, char key[32]);
/// Modify
int dAcc_map_set(dAcc_map * map, char key[32], void * value);

// Map searching
/// Get value
void* dAcc_map_get(dAcc_map * map, char key[32]);
/// Get value as string
char* dAcc_map_gets(dAcc_map * map, char key[32]);
/// Get map
dAcc_map* dAcc_map_getm(dAcc_map * map, char key[32]);

// Map info
/// view all values
void dAcc_map_inspect(dAcc_map * map);
/// number of entries/occurances
int dAcc_map_len(dAcc_map * map);
int dAcc_map_count(dAcc_map * map, void * value);

#ifdef __cplusplus
}
#endif

// EOF
