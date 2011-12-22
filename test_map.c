/**
 * @file test_map.c
 * @author Henry Rapley <photofroggy>
 * @version 1
 *
 * @section DESCRIPTION
 *
 * This program is simply to make sure my stuff works as I make it. Also
 * doubles as a demonstration of how maps can be used.
 */

#include <stdio.h>
#include <string.h>
#include "dAcc/map.h"

int main(void) {

    dAcc_map * map;
    
    // test basic creation and inspection.
    map = dAcc_map_new("foo", "bar");
    dAcc_map_inspect(map);
    printf("map size: %i\n", dAcc_map_len(map));
    
    printf("-- Setting -----\n");
    
    // Adding k-v pairs.
    dAcc_map_set(map, "lol", "wot");
    dAcc_map_inspect(map);
    
    printf("---- override --\n");
    
    // Overriding.
    dAcc_map_set(map, "lol", "dick");
    dAcc_map_inspect(map);
    
    printf("-- Get ---------\n");
    
    // Getting
    printf(">> lol = %s\n", dAcc_map_gets(map, "lol"));
    // Should be empty string.
    printf(">> t = %s\n", dAcc_map_gets(map, "t"));
    
    printf("-- Deletion ----\n");
    
    // Deleting
    dAcc_map_remove(map, "dick");
    dAcc_map_inspect(map);
    dAcc_map_remove(map, "foo");
    dAcc_map_inspect(map);
    dAcc_map_set(map, "foo", "bar");
    dAcc_map_inspect(map);
    dAcc_map_remove(map, "foo");
    dAcc_map_inspect(map);
    dAcc_map_set(map, "foo", "bar");
    
    printf("-- Counting ----\n");
    printf(">> found \"bar\" %i times\n", dAcc_map_count(map, "bar"));
    
    return 0;

}


// EOF
