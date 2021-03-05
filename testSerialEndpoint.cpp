#include "SerialEndpoint.hpp"
#include "ISerial.hpp"


std::vector<uint8_t> recvBuff;

constexpr auto print_frame=[](auto& frame)
{
    for(auto e:frame)
    {
       std::cout<<std::hex<<static_cast<int>(e)<<" ";
    }
    std::cout<<"\n";
};

struct MySerialDevice: public ISerial
{
    MySerialDevice(){}
    void transmit(uint8_t *buff,size_t size) override
    {
      // HAL_UART_Transmit
        for(size_t i=0;i<size;i++)
        {
            std::cout<<std::hex<<static_cast<int>(buff[i])<<" ";    
            recvBuff.push_back(buff[i]);  
        }
        std::cout<<"\n\n";
    }
    void receive(uint8_t ch) override
    {
        
    }
};


MySerialDevice dev;
SerialEndPoint ser0(&dev);

void ISR()
{
    for(auto e:recvBuff)
    {
        ser0.receive(e);
    }

}


int main()
{
    

    uint8_t buffer[]={0x61,0x62,0x12,0x13,0x14,0x63,0x64,0x65};
    ser0.writeEndpoint(buffer,8);

    // Emulate ISR
    ISR();

    // Get Frame from endpoint
    auto recvBuff=ser0.try_getFrame();
    print_frame(recvBuff);
    return 0;
}
