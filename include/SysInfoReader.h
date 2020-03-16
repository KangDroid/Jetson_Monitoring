#include <iostream>

// Syscall stuff
#include <sys/sysinfo.h>
#include <linux/unistd.h>
#include <linux/kernel.h>

using namespace std;

class SysInfoReader {
private:
    struct sysinfo systemInfo;
    int errorCode;
public:
    long getUptime();
    double getFreeRamPercentage();
};