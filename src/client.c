#include "client.h"
#include "conn.h"
#include "var.h"
#include "packet.h"

extern ConnectionList list;


// this is ran in a new thread everytime, be aware
DWORD WINAPI HandleClient(void* content){
    Connection* con = (Connection*)content;
    tcp_socket client = con->socket;
    netlib_tcp_accept(client);
    printf("connected!\n");
    char buffer[512];
    while(1){ 
        int packetLength = ReadVarInt(client);
        if(packetLength == -1){
            break;
        }
        printf("packet length: %d\n", packetLength);
        int packet = ReadVarInt(client);
        if(packetLength == -1){
            break;
        }
        printf("packet: 0x%x\n", packet);
        if (packet == 0x00) { 
            LoginRequestPacket pack = GetLoginRequest(client);
            printf("%s\n", pack.username);
            LoginSuccessPacket suc = GetLoginSuccess(client);
            printf("%s\n", suc.username);
        }
    }
    con->active = false;
    netlib_tcp_close(client);
    return 0;
}