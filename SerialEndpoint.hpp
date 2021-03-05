#ifndef __SERIAL_ENDPOINT_H__
#define __SERIAL_ENDPOINT_H__

#include "ISerial.hpp"
#include "FrameDecoderSm.h"
#include "FrameEncoderSm.h"


struct SerialEndPoint
{
    SerialEndPoint(ISerial* ser):mDevice(ser)
    {

    }
    void writeEndpoint(uint8_t *buff,size_t size)
    {
        // Sm process
        m_encoder.pushEncoder(buff,size);

        // createBuffer
        auto encodedframe=m_encoder.getFrame().value();
        uint8_t* encoded_buff=encodedframe.data();
        size_t  encoded_len=encodedframe.size();

        mDevice->transmit(encoded_buff,encoded_len);
        
    }
    std::vector<uint8_t> try_getFrame()
    {
        if(m_decoder.availableFrames()>0)
        {
            auto decodedframe=m_decoder.getFrame().value();
            return decodedframe;
        }
        return {};
    }
    void receive(uint8_t ch)
    {
        m_decoder.pushToDecoder(ch);
    }
    private:
        ISerial* mDevice;
        FrameEncoder m_encoder;
        FrameDecoder m_decoder;
};



#endif