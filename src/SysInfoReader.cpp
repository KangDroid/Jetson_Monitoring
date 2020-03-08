#include "SysInfoReader.h"

long SysInfoReader::getUptime() {
    errorCode = sysinfo(&systemInfo);
    if (errorCode != 0) {
        return 0;
    } else {
        return systemInfo.uptime;
    }
}