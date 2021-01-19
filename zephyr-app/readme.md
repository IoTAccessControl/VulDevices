
## Build

#### Nrf52840
west build -b nrf52840_PCA10056 . 

Flash:  
nrfjprog -f nrf52 --program E:\PaperWork\IoT\OS\IoTPatch\VulDevices\zephyr-app\build\zephyr\zephyr.hex --sectorerase --reset  

#### stm32L475
west build -b disco_l475_iot1 .  
st-flash --reset write E:\PaperWork\IoT\OS\IoTPatch\VulDevices\zephyr-app\build\zephyr\zephyr.bin 0x08000000   
需要擦除后，才能用keil继续刷：st-flash erase  
stlink工具：https://github.com/stlink-org/stlink（最新版windows下有bug，需要自己编译）  
