/**
 * @file dAcc/packet.h
 * @author Henry Rapley <photofroggy>
 * @version 1
 *
 * @section DESCRIPTION
 *
 * Code for the dAcc_packet functions.
 */

#include <string.h>
#ifndef dAcc_map
#include "map.h"
#endif
#include "packet.h"

/**
 * Create an empty packet object.
 */
dAcc_packet* dAcc_packet_empty() {

    dAcc_packet *pkt = malloc(sizeof(dAcc_packet));
    pkt->command[0] = '\0';
    pkt->param[0] = '\0';
    pkt->args = dAcc_map_empty();
    pkt->body[0] = '\0';
    pkt->subpacket = NULL;
    return pkt;

}

/**
 * Parses a dAmn packet and returns it as a dAcc_packet object.
 */
dAcc_packet* dAcc_packet_parse(char* packet) {
    
    if(packet[0] == '\0')
        return NULL;
    
    dAcc_packet *pkt = dAcc_packet_empty();
    char * sep = strstr(packet, "\n\n");
    char head[8092];
    char line[1000];
    int item = 0;
    dAcc_map * targ;
    
    /* If there is a packet body, we may as well handle that first, as this
     * parser is not interested in subpackets (yet). So, we look for two line
     * breaks, as in strstr above, and then copy the header into a separate
     * string.
     */
    if(sep == 0) {
        strcpy(head, packet);
    } else {
        strncpy(head, packet, sep - packet);
        strcpy(pkt->body, sep + 2);
    }
    
    
    // Process each line under the command and param in the header.
    // Use a do...while to make sure single-line headers are processed.
    do {
        // Find the end of the line.
        sep = strchr(head, '\n');
        
        if(sep != NULL) {
            // Copy the first line to `line`.
            strncpy(line, head, sep - head);
            // Make sure the last character is nul.
            line[sep - head] = '\0';
            // Copy the rest of the header into `head`.
            strcpy(head, sep + 1);
        } else {
            // Copy the header into `line` if we are on the last line.
            strcpy(line, head);
        }
        
        // Parse `line` as an arg or as command and/or param.
        if(item == 0) {
            targ = dAcc_packet_parsearg(line, ' ');
        } else {
            targ = dAcc_packet_parsearg(line, '=');
        }
        
        if(targ != NULL) {
            if(item == 0) {
                strcpy(pkt->command, targ->key);
                strcpy(pkt->param, (char*) targ->value);
            } else {
                // Add the arg if parsed successfully.
                dAcc_map_set(pkt->args, targ->key, targ->value);
            }
        } else if(item == 0) {
            strcpy(pkt->command, line);
        }
        
        item++;
        
    } while(sep != NULL);
    
    return pkt;
}

/**
 * Parse an argument line.
 */
dAcc_map* dAcc_packet_parsearg(char * line, int separator) {

    char * spos = strchr(line, separator);
    
    if(spos == NULL) {
        return NULL;
    }
    
    dAcc_map *arg = dAcc_map_empty();
    strncpy(arg->key, line, spos - line);
    strcpy(arg->value, spos + 1);
    
    arg->key[spos - line] = '\0';
    ((char*)arg->value)[strlen(spos + 1)] = '\0';
    
    return arg;
}



// EOF
