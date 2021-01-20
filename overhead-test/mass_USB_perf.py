import usb.core
import struct
import time

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
        dev.write(1, cbw)

        dev.write(1, b"\x00" * 0x200)

        # time.sleep(0.1)

        dev.clear_halt(1)

        dev.read(0x81, 0x40)
        
        dev.ctrl_transfer(0x20, 0xFF, 0, 0)
        
        cb = p8(0xA8) + p8(0) + p32b(0) + p32b(1)
        cbw = b"USBC" + p32(0x11223344) + p32(0x200) + p8(0x80) + p8(0) \
            + p8(len(cb)) + cb

        cbw += b"\x00" * (31 - len(cbw))
        dev.write(1, cbw)
        data = bytes(dev.read(0x81, 0x200))

        dev.read(0x81, 0x40)

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

def main():
    dev = usb.core.find(idVendor=0x2fe3, idProduct=0x0100)

    for cfg in dev:
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