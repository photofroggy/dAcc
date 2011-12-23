/**
 * @file dAcc/packet.h
 * @author Henry Rapley <photofroggy>
 * @version 1
 *
 * @section DESCRIPTION
 *
 * Header file defining the structs, types and functions relating to the
 * dAcc_packet type.
 */


#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dAcc_packet dAcc_packet;

/**
 * Packet data structure.
 * This data structure represents a packet like the ones used in dAmn's
 * protocol. The format of these packets is as such::
 * 
 *      command param
 *      arg1=value1
 *      arg2=value2
 *      
 *      body
 *
 * The `param` and packet arguments are optional. The body is also optional,
 * but there are always two newlines after the header. The header consists of
 * the command value, the param value, and any arguments present. The body of
 * the packet may also contain a sub packet, following the same format.
 */
struct dAcc_packet {
    char event[12];          //!< Packet event.
    char command[100] ;      //!< Packet command.
    char param[100];         //!< Packet parameter.
    dAcc_map * args;         //!< Packet arguments.
    char body[8092];         //!< Packet body.
    dAcc_packet * subpacket; //!< Subpacket pointer. Not used by default.
};

dAcc_packet* dAcc_packet_empty();

dAcc_packet* dAcc_packet_create(char * packet);

dAcc_packet* dAcc_packet_parse(char * packet);

dAcc_map* dAcc_packet_parsearg(char * line, int separator);

char* dAcc_packet_event(dAcc_packet * pkt);


#ifdef __cplusplus
}
#endif

// EOF
