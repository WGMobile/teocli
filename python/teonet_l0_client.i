/* teonet_l0_client.i */
%module teocli
%{
/* Put header files here or function declarations like below */
#include "../libteol0/teonet_l0_client.h"    
    
//extern size_t teoLNullPacketCreate(char* buffer, size_t buffer_length, 
//        uint8_t command, const char * peer, const char * data, size_t data_length);
//extern size_t teoLNullInit(char* buffer, size_t buffer_length, const char* host_name);    
%}

extern size_t teoLNullPacketCreate(char* buffer, size_t buffer_length, 
        int command, const char * peer, const char * data, size_t data_length);
extern size_t teoLNullPacketCreateLogin(char* buffer, size_t buffer_length, const char* host_name);
