# src Directory
This is the root directory of all the sources of this framework.

| Folder                   | Description                                                |
| ------------------------ | ---------------------------------------------------------- |
| [arch](src/arch)         | Constitues of all cpu architecture related sources         |
| [driver](src/driver)     | Constitues of device driver sources                        |
| [engine](src/engine)     | Constitues of framework's entrypoint source file           |
| [include](src/include)   | Constitues of all the include/header files except for arch |
| [lib](src/lib)           | Constitues of all the necessary libraries                  |
| [platform](src/platform) | Constitues of platform/dev-board specific sources          |
| [projects](src/projects) | Constitues of project sources made using this framework    |
| [visor](src/visor)       | Constitues of terra/hyper/super - visors' sources          |

---

#### [sources.mk](src/sources.mk)
This build scipt collates various paraments used by build engine and build scripts from other sub directories
