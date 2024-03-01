#pragma once

#ifndef _PS3_H_
#define _PS3_H_

#include <stdint.h>

#include "usbh/tusb_hid/shared.h"

const usb_vid_pid_t ps3_devices[] = 
{
    {0x054C, 0x0268}, // Sony Batoh (Dualshock 3)
    // {0x045E, 0x028E}, // Voyee generic "P3", won't work, IDs are for a 360 controller (dumb)
    {0x044F, 0xB324}, // ThrustMaster Dual Trigger (PS3 mode)
    {0x0738, 0x8818}, // MadCatz Street Fighter IV Arcade FightStick
    {0x0810, 0x0003}, // Personal Communication Systems, Inc. Generic
    {0x146B, 0x0902} // BigBen Interactive Wired Mini PS3 Game Controller
};

struct DualShock3Report
{
    uint8_t reportId;
    uint8_t unk0;

    uint8_t select : 1;
    uint8_t l3     : 1;
    uint8_t r3     : 1;
    uint8_t start  : 1;
    uint8_t up     : 1;
    uint8_t right  : 1;
    uint8_t down   : 1;
    uint8_t left   : 1;

    uint8_t l2       : 1;
    uint8_t r2       : 1;
    uint8_t l1       : 1;
    uint8_t r1       : 1;
    uint8_t triangle : 1;
    uint8_t circle   : 1;
    uint8_t cross    : 1;
    uint8_t square   : 1;

    uint8_t ps : 1;
    uint8_t    : 0;

    uint8_t unk1;

    uint8_t leftX;
    uint8_t leftY;
    uint8_t rightX;
    uint8_t rightY;

    uint8_t unk2[31];

    int16_t accelerX;
    int16_t accelerY;
    int16_t accelerZ;

    int16_t velocityZ;
}
__attribute__((packed));

struct Dualshock3State
{
    bool report_enabled {false};
    uint8_t dev_addr = {0};
    uint8_t instance = {0};
};

class Dualshock3
{
    public:
        Dualshock3State dualshock3;

        void init(uint8_t dev_addr, uint8_t instance);
        void process_report(uint8_t const* report, uint16_t len);
        bool send_fb_data();
        
    private:
        bool enable_report();
        void reset_state();
        void update_gamepad(const DualShock3Report* ds3_data);
};

// bool init_dualshock3(uint8_t dev_addr, uint8_t instance);
// bool send_fb_data_to_dualshock3(uint8_t dev_addr, uint8_t instance);
// void process_dualshock3(uint8_t const* report, uint16_t len);

#endif // _PS3_H_