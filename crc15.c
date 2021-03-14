#include<stdio.h>
#include <stdint.h>
#include<stdlib.h>
#include<string.h>

#define POLYNOMIAL 0x1B // The CAN protocol uses the CRC-15 with this polynomial

int main(void)
{
    unsigned int message = 0xE5;
    unsigned int crc=message; 
    unsigned int checksum=message;
    int i;
    printf("Message is: %#x\t", message);  

    for(i=0;i<4;i++) 
    {

        if(crc>0xF)
        {
            crc=crc^POLYNOMIAL;
        }
        crc=crc<<1;
    }
    printf("CRC:%#x\t",crc); 


    return 0;
}