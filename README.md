# ![Cyancore](./icons/cyancore_50x50.png)  Cyancore Framework
###### *A unified software platform for embedded system projects ...*
---

> **Version (arch:2 | major:4 | minor:2): 0.1.0**

[![SonarCloud](https://sonarcloud.io/images/project_badges/sonarcloud-white.svg)](https://sonarcloud.io/summary/new_code?id=VisorFolks_cyancore)
[![GitHub CI](https://github.com/VisorFolks/cyancore/actions/workflows/github_ci.yml/badge.svg)](https://github.com/VisorFolks/cyancore/actions/workflows/github_ci.yml)
[![Lines of code](https://img.shields.io/tokei/lines/github/visorfolks/cyancore?label=Lines%20of%20code)]()
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=VisorFolks_cyancore&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=VisorFolks_cyancore)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=VisorFolks_cyancore&metric=bugs)](https://sonarcloud.io/summary/new_code?id=VisorFolks_cyancore)
[![Security Rating](https://sonarcloud.io/api/project_badges/measure?project=VisorFolks_cyancore&metric=security_rating)](https://sonarcloud.io/summary/new_code?id=VisorFolks_cyancore)

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
| ATMega328P | FE310-G002  | Coming soon | Coming soon | Coming soon  |
| ATMega2560 |             |             |             |              |

### Projects
run
```sh
$ make list
```

### Programming Languages
* asm/assembly
* C/C++
* makefile
* linker script

### Help
run
```sh
$ make help
```

For details about the framework, follow the README.md in each folder.

### Requirements

Host system requirements:
* Linux Machine (WSL/Dedicated machine)
* make utility and cppcheck installed; run 
```sh
  $ sudo apt install build-essential cppcheck -y
```


Toolchain Requirements:
* Please push your toolchains to your git repo
* Update the links in mk/tc_get.mk file
* run ```$ make help``` for more details
