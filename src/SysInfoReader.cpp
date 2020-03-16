#include "SysInfoReader.h"

long SysInfoReader::getUptime() {
    errorCode = sysinfo(&systemInfo);
    if (errorCode != 0) {
        return 0;
    } else {
        return systemInfo.uptime;
    }
}

double SysInfoReader::getFreeRamPercentage() {
    errorCode = sysinfo(&systemInfo);
    if (errorCode != 0) {
        return 0;
    } else {
        unsigned long freeram = systemInfo.freeram;
        unsigned long totalram = systemInfo.totalram;
        return (((double)freeram/totalram) * 100);
    }
}