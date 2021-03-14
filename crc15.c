#include<stdio.h>
#include <stdint.h>
#include<stdlib.h>
#include<string.h>

#define POLYNOMIAL 0xC599U // The CAN protocol uses the CRC-15 with this polynomial

int bitNumber(unsigned int x)  //Return binary bits
{
    int i=0;
    do
    {
        x=x>>1;
        i++;
    } 
    while(x>0);
    return i; 
}

unsigned crc15checksum(unsigned int x) //Return CRC
{
    printf("Message is: %c\t",x);  
    int i;
    unsigned mes=x; 
    for(i=0;i<15;i++) 
    {
        x=x<<1;
        if(x>0x7FFF)
        {
            x=x^POLYNOMIAL;
        }
    }
    printf("CRC:%#x\t",x); 
    mes=mes<<15;
    mes=mes|x; //Append CRC to message
    printf("Checksummed message=%#x\t",mes); //Print message with CRC
    return mes;
}

char validation(unsigned int x) //Return validation result
{
    unsigned int y=x;
    int le=1;
    if(x==0)
    {
        return 0;
    }
    if(x!=0)
    {
        while(le)
        {
            le=bitNumber(y)-bitNumber(POLYNOMIAL);//calculate bits difference of message and poly
            y=y^(POLYNOMIAL<<le); 
            
            if(y==0) 
            {
                printf("The data is OK\t"); 
                return x>>15; //Return original message; 
            }

        }
        if(y!=0)
            {
                printf("The data is not OK\t"); 
            }
    }
    
    return 'N'; //Return 'N' if message is not char; 
}

int main(void)
{
    int i,j;
    char message[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', 0, 0};
    unsigned int m; 

    j=strlen(message);
    for(i=0;i<j;i++)
    {
        m=crc15checksum(message[i]); //Print message, CRC, Checksummed message;
        printf("%#x\n", validation(m)); //Print validation result and original message in hex; 
     
    }

    return 0;
}