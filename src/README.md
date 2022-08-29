# src Directory
This is the root directory of all the sources of this framework.

| Folder               | Description                                                |
| -------------------- | ---------------------------------------------------------- |
| [arch](arch)         | Constitues of all cpu architecture related sources         |
| [driver](driver)     | Constitues of device driver sources                        |
| [engine](engine)     | Constitues of framework's entrypoint source file           |
| [include](include)   | Constitues of all the include/header files except for arch |
| [lib](lib)           | Constitues of all the necessary libraries                  |
| [platform](platform) | Constitues of platform/development board specific sources  |
| [visor](visor)       | Constitues of terra/hyper/super - visors' sources          |

---

#### [sources.mk](sources.mk)
This build scipt collates various paraments used by build engine and build scripts from other sub directories
