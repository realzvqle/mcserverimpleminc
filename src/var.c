#include "var.h"
#include "exfiles/netlib.h"


#define SEGMENT_BITS 0x7F
#define CONTINUE_BIT 0x80

byte ReadByte(tcp_socket sock){
    byte b;
    int recv = netlib_tcp_recv(sock, &b, sizeof(byte));
    if(recv <= 0){
        if(recv == 0){
            info("One Client Disconnected!\n");
        } else {
            fail("Error: %s\n", netlib_get_error());
        }
        return (byte)-1;
    } 
    return b;
}

void WriteByte(tcp_socket sock, byte b){
    int recv = netlib_tcp_send(sock, &b, sizeof(byte));
    if(recv <= 0){
        fail("hmm, writebyte failed??\n");
    } 
}


int IntToVarInt(int integer, uint8_t *output) {
    int length = 0;
    while (true) {
        if ((integer & ~SEGMENT_BITS) == 0) {
            output[length++] = integer;
            return length;
        }
        output[length++] = (integer & SEGMENT_BITS) | CONTINUE_BIT;
        integer >>= 7;
    }
}

int ReadVarInt(tcp_socket sock){
    int value = 0;
    int position = 0;

    byte currentByte;

    while(true){
        currentByte = ReadByte(sock);
        if(currentByte == (byte)-1) return -1;
        value |= (currentByte & SEGMENT_BITS) << position;
        if((currentByte & CONTINUE_BIT) == 0) break;

        position += 7;
        if(position >= 32){
            fail("ReadVarInt failed! VarInt is too large\n");
            return -1;
        }
    }
    return value;
}

long ReadVarLong(tcp_socket sock){
    long value = 0;
    long position = 0;

    byte currentByte;

    while(true){
        currentByte = ReadByte(sock);
        value |= (long) (currentByte & SEGMENT_BITS) << position;
        if((currentByte & CONTINUE_BIT) == 0) break;

        position += 7;
        if(position >= 64){
            fail("ReadVarLong failed! VarInt is too large\n");
            return -1;
        }
    }
    return value;
}

void WriteVarInt(tcp_socket sock, int value){
    while(true){
        if((value & ~SEGMENT_BITS) == 0) {
            WriteByte(sock, value);
            return;
        }   
        WriteByte(sock, (value & SEGMENT_BITS) | CONTINUE_BIT);

        value = (unsigned int)value >> 7;
    }
}


void WriteVarLong(tcp_socket sock, long value){
    while(true){
        if((value & ~((long)SEGMENT_BITS)) == 0) {
            WriteByte(sock, value);
            return;
        }   
        WriteByte(sock, (value & SEGMENT_BITS) | CONTINUE_BIT);

        value = (unsigned long)value >> 7;
    }
}