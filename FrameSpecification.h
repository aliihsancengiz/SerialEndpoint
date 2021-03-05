#ifndef __FRAME_SPEC_H__
#define __FRAME_SPEC_H__


// Specify custom frame layout
struct FrameSpecification
{
    static constexpr uint8_t SofIndicator=0x12,EofIndicator=0x13,ESCIndicator=0x14;
    FrameSpecification()=default;
};



#endif