```
west init -l app
west update
west zephyr-export
west config build.board stm32f411e_disco
west build app
```

[Config west for build](https://docs.zephyrproject.org/latest/develop/west/build-flash-debug.html#configuration-options)

TODO:

- [ ] Test launch and tasks
- [ ] Publish container
