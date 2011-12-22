/**
 * @file dAcc/map.c
 * @author Henry Rapley <photofroggy>
 * @version 1
 *
 * @section DESCRIPTION
 *
 * Code for the dAcc_map functions.
 */

#include <string.h>
#include "map.h"


/*****************************************************************************\
 * CREATION
 * The following functions are helpers for creating new map variables. Hell
 * yeah.
\*****************************************************************************/

/**
 * Create a new, empty, map object.
 *
 * An empty map object is one with `key` set to an empty string and `value` set
 * to a NULL pointer. It's really just a shortcut for making a new map with
 * default values.
 *
 * @return new empty map object.
 */
dAcc_map* dAcc_map_empty() {
    return dAcc_map_new("\0", NULL);
}

/**
 * Create a new map object.
 * 
 * A map object represents an entry in a map. A map is, technically, a linked
 * list made up of map objects. So, every map has at least one entry, but this
 * entry can be empty.
 *
 * @param key - String key associated with the object.
 * @param value - Pointer to the object associated with the key.
 * @return new dAcc_map with `key` and `value` members set to the given input.
 */
dAcc_map* dAcc_map_new(char key[32], void * value) {
    int kl = strlen(key);
    dAcc_map * map = malloc(sizeof(dAcc_map));
    
    strcpy(map->key, key);
    map->key[(kl < 32 ? kl : 31)] = '\0';
    
    map->value = value;
    map->next = NULL;
    
    return map;
}


/*****************************************************************************\
 * MANIPULATION
 * These functions are concerned with manipulating maps with regards to
 * adding, removing and changing items in map. These functions return an
 * integer, 1 for failure, 0 for success.
\*****************************************************************************/

/**
 * Add a key-value pair to a map.
 *
 * If the given key is not already in the given map, this function creates a
 * new map entry for the key-value pair, and adds this object to the given map.
 * Otherwise, the value already associated with the given key is overridden
 * with the value given to this function.
 *
 * @param map - The map to add the pair to.
 * @param key - The key to use.
 * @param value - The value to store.
 * @return 0 - Success.
 * @return 1 - Failure.
 */
int dAcc_map_set(dAcc_map * map, char key[32], void * value) {

    if(map == NULL)
        return 1;
    
    dAcc_map *entry = dAcc_map_getm(map, key);
    
    if(entry != NULL) {
        entry->value = value;
        return 0;
    }
    
    return dAcc_map_append(map, dAcc_map_new(key, value));

}

/**
 * Appends a map entry onto the end of a map.
 *
 * @param head - The map to add the entry to.
 * @param map - The entry to add to the map.
 * @return 0 - Success.
 * @return 1 - Failure.
 */
int dAcc_map_append(dAcc_map * head, dAcc_map * map) {
    
    if(head == NULL || map == NULL)
        return 1;
    
    dAcc_map *temp = head;
    
    while(temp->next != NULL)
        temp = temp->next;
    
    temp->next = map;
    
    return 0;
    
}
/* / Remove item
int dAcc_map_remove(dAcc_map * map, char key[32]);
/* / Modify
int dAcc_map_set(dAcc_map * map, char key[32], void * value);


/*****************************************************************************\
 * SEARCHING
 * The following functions are helpers for retrieving map objects and other
 * items based on a given key.
\*****************************************************************************/

/* / Get value
void* dAcc_map_get(dAcc_map * map, char key[32]);
/* / Get value as string
char* dAcc_map_gets(dAcc_map * map, char key[32]);

/**
 * Get the map entry associated with the given key.
 *
 * @param map - The map to search through.
 * @param key - The key to search for.
 * @return map - Map entry. NULL returned on failure.
 */
dAcc_map* dAcc_map_getm(dAcc_map * map, char key[32]) {
    
    if(map == NULL)
        return NULL;

    dAcc_map *temp = map;
    
    while(1) {
    
        if(!strcmp(temp->key, key))
            return temp;
        
        if(temp->next == NULL)
            return NULL;
    
    }
    
}

/*****************************************************************************\
 * INFORMATION
 * The following functions are helpers for determing details about maps.
\*****************************************************************************/
 
/**
 * Print all of the key-value pairs in the given map.
 *
 * @param map - The map to display all entries for.
 */
void dAcc_map_inspect(dAcc_map * map) {

    dAcc_map * temp = map;
    
    if(temp == NULL)
        return;
    
    printf(">> map data:\n");
    
    while(1) {
        
        printf(">>> %s = %s\n", temp->key, (char*) (temp->value));
        
        if(temp->next == NULL)
            break;
        
        temp = temp->next;
    
    }

}

/**
 * Count the number of entries in a given map.
 *
 * This function will include empty entries.
 *
 * @param map - The map to use when counting.
 * @return int count
 */
int dAcc_map_len(dAcc_map * map) {

    dAcc_map * temp = map;
    
    if(temp == NULL)
        return 0;
    
    int count = 0;
    
    while(1) {
        
        count++;
        
        if(temp->next == NULL)
            break;
        
        temp = temp->next;
    
    }
    
    return count;

}


// EOF
