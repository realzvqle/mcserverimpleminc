#ifndef VAR_H_INCLUDED
#define VAR_H_INCLUDED




#include "superheader.h"

byte ReadByte(tcp_socket sock);
void WriteByte(tcp_socket sock, byte b);
int IntToVarInt(int integer, uint8_t *output);
int ReadVarInt(tcp_socket sock);
void WriteVarInt(tcp_socket sock, int value);
#endif