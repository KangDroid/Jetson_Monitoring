Jetson_Monitoring README
=========================
![C/C++ CI](https://github.com/KangDroid/Jetson_Monitoring/workflows/C/C++%20CI/badge.svg)

What is this?
--------------
Simply monitors CPU Frequency, Load, Thermal Status.<br>
Part of KangDroid CL-OS Project(https://github.com/KangDroid/CL-OS/blob/master/concepts_and_plan.md). <br>
< Mid-Layer between server request and real(actual data) >

Supported Devices
------------------
| Devices | Operating System |
| ------- | ---------------- |
| NVidia Jetson Nano | Ubuntu 18.04(Provided by NVidia) |
| Raspberry Pi 3B | Ubuntu 18.04(64-bit) - Will work on other distro |

Feature(Supported)
-------
- CPU Frequency Monitoring via /sys (Both RPi/Jetson Nano)
- CPU Thermal Monitoring via /sys (Both RPi/Jetson Nano)
- Continous Monitoring

Feature(wishlist)
-------------------
- Graph?
- GPU Thermal Monitoring via /sys (Only Jetson Nano)
- GPU Frequency Monitoring (Only Jetson Nano)
