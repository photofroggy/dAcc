/**
 * @file test_packet.c
 * @author Henry Rapley <photofroggy>
 * @version 1
 *
 * @section DESCRIPTION
 *
 * This program is simply to make sure my stuff works as I make it. Also
 * doubles as a demonstration of how packets can be used.
 */

#include <stdio.h>
#include <string.h>
#include "dAcc/map.h"
#include "dAcc/packet.h"

int main(void) {
    
    dAcc_packet * pkt;
    
    pkt = dAcc_packet_create("recv chat:Botdom\n\nmsg main\nfrom=photofroggy\n\nHere's a message for ya!\0");
    printf("n\n");
    if(pkt->subpacket->args == NULL) {
        printf("failed for some reason\n");
        return 1;
    }
    
    printf(">> EVENT: %s;\n", pkt->event);
    
    printf("[#%s] <%s> %s\n",
        pkt->param + 5,
        dAcc_map_gets(pkt->subpacket->args, "from"),
        pkt->subpacket->body);
    
    return 0;

}


// EOF
