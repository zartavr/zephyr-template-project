Template repository for zephyr based projects

Component versions: 

- zephyr: 3.6
- zartavr/zephyr-devconainer: no tag [link](https://github.com/zartavr/zephyr-devcontainer)

For update zephyr modules:
```
west update
```

For change board
```
west config build.board stm32f411e_disco
```

For build, ref `tasks.json`
```
west build app
```

[Config west for build](https://docs.zephyrproject.org/latest/develop/west/build-flash-debug.html#configuration-options)
