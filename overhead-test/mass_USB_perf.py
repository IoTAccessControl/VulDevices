import usb.core
import struct
import time
import os

os.environ['PYUSB_DEBUG'] = 'debug'

END_POINT = {"read": 0x81, "write": 0x1}
NRF52840_ENDPOINT = {"read": 0x81, "write": 0x1}
STM32L475_ENDPOINT = {"read": 0x83, "write": 0x3}

def p32(x):
    return struct.pack("<I", x)

def p32b(x):
    return struct.pack(">I", x)

def p8(x):
    return struct.pack("<B", x)

def perf_test(dev):
    for i in range(100):
        cb = p8(0xAA) + p8(0) + p32b(0) + p32b(1)
        cbw = b"USBC" + p32(0x11223344) + p32(0x200) + p8(0) + p8(0) \
            + p8(len(cb)) + cb

        cbw += b"\x00" * (31 - len(cbw))
        dev.write(END_POINT["write"], cbw)

        dev.write(END_POINT["write"], b"\x00" * 0x200)

        # time.sleep(0.1)

        dev.clear_halt(END_POINT["write"])

        dev.read(END_POINT["read"], 0x40)
        
        dev.ctrl_transfer(0x20, 0xFF, 0, 0)
        
        cb = p8(0xA8) + p8(0) + p32b(0) + p32b(1)
        cbw = b"USBC" + p32(0x11223344) + p32(0x200) + p8(0x80) + p8(0) \
            + p8(len(cb)) + cb

        cbw += b"\x00" * (31 - len(cbw))
        dev.write(END_POINT["write"], cbw)
        data = bytes(dev.read(END_POINT["read"], 0x200))

        dev.read(END_POINT["read"], 0x40)

    return data

def hexdump(data):
    line = ""
    for x, b in enumerate(data):
        if x % 16 == 0 and line:
            print(line)
            line = ""
        line += "{:02X} ".format(b)

    if line:
        print(line)

def load_backend():
    from usb.backend import libusb1
    return libusb1.get_backend()

# class Device:
#     NRF52840 = 1

def main():
    backend = None
    is_win32 = os.name == 'nt'

    is_nrf52840 = True

    if is_win32:
       backend = load_backend()
    global END_POINT
    if is_nrf52840:
        END_POINT = NRF52840_ENDPOINT
        dev = usb.core.find(idVendor=0x2fe3, idProduct=0x0100, backend=backend)
    else:
        dev = usb.core.find(idVendor=0x0483, idProduct=0x374b, backend=backend)
        END_POINT = STM32L475_ENDPOINT

    if not is_win32:
        for cfg in dev:
            print(cfg)
            for intf in cfg:
                if dev.is_kernel_driver_active(intf.bInterfaceNumber):
                    try:
                        dev.detach_kernel_driver(intf.bInterfaceNumber)
                    except usb.core.USBError as e:
                        raise RuntimeError("detach_kernel_driver")
    
    data = perf_test(dev)
    hexdump(data)

if __name__ == "__main__":
    main()