```
west init -l app
west update
west zephyr-export
west config -l
west build -b stm32f4_disco -t guiconfig
```