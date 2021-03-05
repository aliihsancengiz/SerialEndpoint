#ifndef __ISerial_H__
#define __ISerial_H__

#include <cstdint>
#include <iostream>

/*
*   Serial Interface to decouple device from endpoint
*/
struct ISerial
{
    virtual void transmit(uint8_t *buff,size_t size)=0;
    virtual void receive(uint8_t ch)=0; 
};

#endif