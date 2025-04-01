#include "packet.h"
#include "var.h"



void SendLoginRequest(tcp_socket sock, LoginRequestPacket* packet){
    WriteVarInt(sock, packet->packet_id);
    for(int i = 0; i < 16; i++){
        if(packet->username[i] == '\n' || packet->username[i] == '\0'){
            WriteVarInt(sock, 0);
            continue;
        } 
        WriteVarInt(sock, packet->username[i]);
        
    }
    WriteVarInt(sock, packet->next_state);
    
}


LoginRequestPacket GetLoginRequest(tcp_socket sock){
    LoginRequestPacket packet;
    packet.packet_id = ReadVarInt(sock);
    for(int i = 0; i < 16; i++){
        packet.username[i] = ReadVarInt(sock);
    }
    packet.next_state = ReadVarInt(sock);
    return packet;
}

LoginSuccessPacket GetLoginSuccess(tcp_socket sock){
    LoginSuccessPacket packet;
    packet.uuid[0] = ReadVarInt(sock);
    packet.uuid[1] = ReadVarInt(sock);
    for(int i = 0; i < 16; i++){
        packet.username[i] = ReadVarInt(sock);
    }
    for(int i = 0; i < 64; i++){
        packet.property.string[i] = ReadVarInt(sock);
    }
    for(int i = 0; i < 32767; i++){
        packet.property.anotherstring[i] = ReadVarInt(sock);
    }
    for(int i = 0; i < 1024; i++){
        packet.property.optionalstring[i] = ReadVarInt(sock);
    }
    return packet;
}

void SendLoginSuccess(tcp_socket sock, LoginSuccessPacket* packet){
    WriteVarInt(sock, packet->uuid[0]);
    WriteVarInt(sock, packet->uuid[1]);
    for(int i = 0; i < 16; i++){
        if(packet->username[i] == '\n' || packet->username[i] == '\0'){
            WriteVarInt(sock, 0);
            continue;
        } 
        WriteVarInt(sock, packet->username[i]);
    }
    for(int i = 0; i < 64; i++){
        if(packet->property.string[i] == '\n' || packet->property.string[i] == '\0'){
            WriteVarInt(sock, 0);
            continue;
        } 
        WriteVarInt(sock, packet->property.string[i]);
    }
    for(int i = 0; i < 32767; i++){
        if(packet->property.anotherstring[i] == '\n' || packet->property.anotherstring[i] == '\0'){
            WriteVarInt(sock, 0);
            continue;
        } 
        WriteVarInt(sock, packet->property.anotherstring[i]);
    }
    for(int i = 0; i < 1024; i++){
        if(packet->property.optionalstring[i] == '\n' || packet->property.optionalstring[i] == '\0'){
            WriteVarInt(sock, 0);
            continue;
        } 
        WriteVarInt(sock, packet->property.optionalstring[i]);
    }
    
}