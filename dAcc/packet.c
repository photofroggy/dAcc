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
    pkt->event[0] = '\0';
    pkt->command[0] = '\0';
    pkt->param[0] = '\0';
    pkt->args = NULL;
    pkt->body[0] = '\0';
    pkt->subpacket = NULL;
    return pkt;

}

/**
 * Parses a dAmn packet and returns it as a dAcc_packet object.
 *
 * This object also sets the event name for the packet.
 *
 * @param packet - A dAmn packet formatted string.
 * @return packet object. NULL on failure.
 */
dAcc_packet* dAcc_packet_create(char* packet) {

    dAcc_packet *pkt = malloc(sizeof(dAcc_packet));
    pkt = dAcc_packet_parse(packet);
    
    if(pkt == NULL)
        return NULL;
    
    char* event = dAcc_packet_event(pkt);
    strcpy(pkt->event, event);
    
    return pkt;

}

/**
 * Parses a dAmn packet and returns it as a dAcc_packet object.
 *
 * @param packet - A string formatted as a dAmn packet.
 * @return packet object. Returns NULL on failure.
 */
dAcc_packet* dAcc_packet_parse(char* packet) {
    
    if(packet[0] == '\0')
        return NULL;
    
    dAcc_packet *pkt = dAcc_packet_empty();
    char * sep = strstr(packet, "\n\n");
    char head[8092];
    char line[100];
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
            strncpy(line, head, (sep - head));
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
                if(pkt->args == NULL) {
                    pkt->args = targ;
                } else {
                    dAcc_map_set(pkt->args, targ->key, targ->value);
                }
                dAcc_map_inspect(pkt->args);
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
 *
 * This function splits `line` according to `separator`. A map object is
 * created using the first and second parts of the line as the key and value
 * of the map entry, respectively.
 *
 * @param line - String to split.
 * @param separate - Character to split the string at.
 * @return map object.
 */
dAcc_map* dAcc_packet_parsearg(char * line, int separator) {
    
    char * spos = strchr(line, separator);
    
    if(spos == NULL) {
        return NULL;
    }
    
    dAcc_map *arg = dAcc_map_empty();
    strncpy(arg->key, line, spos - line);
    arg->key[spos - line] = '\0';
    
    char * value = malloc(sizeof(char*));
    strcpy(value, spos + 1);
    value[strlen(spos + 1)] = '\0';
    dAcc_map_set(arg, arg->key, value);
    
    return arg;
}


/**
 * Determine the event name of a given packet.
 *
 * There are packets of certain types. The event name for a packet is set to
 * the packet's command. Packets where the command is "recv" have an event name
 * set to the packet's command, and the subpacket's command. If the subpacket's
 * command is "admin", then the event name includes the subpacket's `param`.
 *
 * @param packet - Packet to get the event name of.
 * @return event - Packet event name.
 */
char* dAcc_packet_event(dAcc_packet * pkt) {
        char * name = pkt->command;
        
        if(strcmp(name, "recv")) {
            strcat(name, "\0");
            return name;
        }
        
        pkt->subpacket = dAcc_packet_parse(pkt->body);
            
        if(pkt->subpacket == NULL) {
            strcat(name, "\0");
            return name;
        }
        
        strcat(name, "_");
        strcat(name, pkt->subpacket->command);
            
        if(strcmp(pkt->subpacket->command, "admin")) {
            strcat(name, "\0");
            return name;
        }
        
        strcat(name, "_");
        strcat(name, pkt->subpacket->param);
        
        return name;
}


// EOF
