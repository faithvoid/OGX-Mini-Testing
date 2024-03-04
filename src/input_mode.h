#ifndef INPUT_MODE_H_
#define INPUT_MODE_H_

#ifdef __cplusplus
extern "C" {
#endif

enum InputMode
{
    INPUT_MODE_XINPUT,
    INPUT_MODE_SWITCH,
    // INPUT_MODE_HID,
    // INPUT_MODE_KEYBOARD,
    INPUT_MODE_PSCLASSIC,
    INPUT_MODE_XBOXORIGINAL,
    // INPUT_MODE_CONFIG,
};

enum InputMode get_input_mode();

#ifdef __cplusplus
}
#endif

#endif // INPUT_MODE_H_