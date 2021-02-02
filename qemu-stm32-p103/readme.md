
#### Usage  
Set arm-none-eabi TOOLCHAIN:  
```
# cmake line 8: modify to your path
set(TOOLCHAIN_PREFIX /mnt/f/IoT/Tools/gcc-arm-none-eabi-9-2020-q2-update/)
```

Running...  
```
mkdir build
cd build && cmake ..
make qemu
```