Jetson_Monitoring(Server-Side) README
=========================
![C/C++ CI](https://github.com/KangDroid/Jetson_Monitoring/workflows/C/C++%20CI/badge.svg)

What is this?
--------------
Simply monitors CPU Frequency, Load, Thermal Status.<br>
Part of KangDroid CL-OS Project(https://github.com/KangDroid/CL-OS/blob/master/concepts_and_plan.md). <br>
< Mid-Layer between server request and real(actual data) >

Difference between Master branch & server-side branch
---------------------------------------------------------
This will outputs the file called "cpu_log" to execution-pwd directory.<br>
The only difference between master/server-side branch is to stream information to STDOUT or single file.<br>
Reason why I need as file stream is to push data to server.<br>
The structure of cpu_log is definetly will same as STDOUT(master branch).

TODO
----
Currently, server-side uses ofstream(open, close) function to handle cpu_log file.<br>
But thinking of efficiency, it isn't really efficient for close-open per every while iteration. <br>
So, maybe using system call would be more efficient, but which call do I need to use..?

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
