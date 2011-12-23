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
    printf("hey\n");
    pkt = dAcc_packet_parse("foo bar\nlol=wot\nfuck=shit\n\nbloody fucking body\0");
    printf("sup\n");
    printf(">> cmd: %s; param: %s;\n", pkt->command, pkt->param);
    dAcc_map_inspect(pkt->args);
    printf(">> body:\n%s\n", pkt->body);
    
    return 0;

}


// EOF
