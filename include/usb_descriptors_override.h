#ifndef USB_DESCRIPTORS_OVERRIDE_H
#define USB_DESCRIPTORS_OVERRIDE_H

#ifdef USB_PRODUCT
#undef USB_PRODUCT
#endif
#define USB_PRODUCT "Borguino Joystick"

#ifdef USB_MANUFACTURER
#undef USB_MANUFACTURER
#endif
#define USB_MANUFACTURER "Borguino"

#ifdef USB_PID
#undef USB_PID
#endif
#define USB_PID 0x0040

// #ifdef USB_VID
// #undef USB_VID
// #endif
// #define USB_VID 0x2341

#endif
