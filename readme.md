
## Setup
mkdir IoTPatch  
将当前项目和PatchCore都放在IoTPatch目录下。  

TODO: 组织成submodule模式。

目录结构：  
IoTPatch  
 | PatchCore (git clone https://github.com/IoTAccessControl/PatchCore.git)  
 | VulDevices (git clone https://github.com/IoTAccessControl/VulDevices.git)  

## Build
zephyr源码修改：  
目前是直接手动修改，后面改成利用git patch工具去修改。  
由于官方的__debug_monitor没有加weak，因此链接时和我们自定义的函数冲突了，要注释掉官方的debug_monitor实现：  
修改zephyrproject\zephyr\arch\arm\core\fault_s.S,注释：  
``` bash
32行 # GTEXT(__debug_monitor)
72行 # SECTION_SUBSEC_FUNC(TEXT,__fault,__debug_monitor)
```

#### USB Mass Build 
west build -b nrf52840_PCA10056 .  -- -DOVERLAY_CONFIG=overlay-usbmass.conf  
windwos上需要使用libusbK驱动