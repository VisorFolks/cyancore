# ![Cyancore](./icons/cyancore_50x50.png)  Cyancore Framework
###### *A unified software platform for embedded system projects ...*
---

> **Version (arch:2 | major:4 | minor:2): 0.1.0**

![GitHub branch checks state](https://img.shields.io/github/checks-status/VisorFolks/cyancore/stable?label=Build%20Status)
![Lines of code](https://img.shields.io/tokei/lines/github/visorfolks/cyancore?label=Lines%20of%20code)
```
arch  : 0x00
major : 0x0001
minor : 0x00
```

### Discord Community
[![Discord](https://discord.com/assets/cb48d2a8d4991281d7a6a95d2f58195e.svg)](https://discord.gg/gxUQr77MT2)

Click the above icon to connect

### Supported Platforms

| Atmel      | SiFive      | STMicro     | TI          | Raspberry Pi |
| ---------- | ----------- | ----------- | ----------- | -------------|
| ATMega328P | Coming soon | Coming soon | Coming soon | Coming soon  |

### Projects
* demo_avr
* demo_avr_cpp
* demo_avr_bit_banding

### Programming Languages
* asm/assembly
* C
* Cpp/C++
* makefile
* linker script

### Help
run
```
make help
```

For details about the framework, follow the README.md in each folder.

### Requirements

Host system requirements:
* Linux Machine (WSL/Dedicated machine)
* make utility and cppcheck installed; run `$ sudo apt install build-essential cppcheck -y`


Toolchain Requirements:
* Please push your toolchains to your git repo
* Update the links in mk/tc_get.mk file
* run ```make help``` for more details
