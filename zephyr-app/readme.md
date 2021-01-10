
## Build

#### Nrf52840
west build -b nrf52840_PCA10056 . 

Flash:  
nrfjprog -f nrf52 --program E:\PaperWork\IoT\OS\IoTPatch\VulDevices\zephyr-app\build\zephyr\zephyr.hex --sectorerase --reset  

#### stm32L475
west build -b disco_l475_iot1 .  

