#ifndef PACKET_H_INCLUDED
#define PACKET_H_INCLUDED






#include "superheader.h"


typedef struct {
    uint8_t packet_id;       
    char username[16];       
    uint8_t next_state;      
} LoginRequestPacket;

typedef struct {
    char string[64];
    char anotherstring[32767]; // bruh
    char optionalstring[1024];
} PrefixedArray; // ??????????????????????????????????????????????????

typedef struct {
    uint64_t uuid[2];
    char username[16];
    PrefixedArray property;
} LoginSuccessPacket;

void SendLoginRequest(tcp_socket sock, LoginRequestPacket* packet);
LoginRequestPacket GetLoginRequest(tcp_socket sock);
LoginSuccessPacket GetLoginSuccess(tcp_socket sock);
#endif