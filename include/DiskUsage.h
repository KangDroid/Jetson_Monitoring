#include <sys/statvfs.h>
#include <iostream>

class DiskUsage {
public:
    /**
     * Disk Array;
     * 0: total;
     * 1: Free;
     * 2: used rate(percentage);
     */
    long long diskArray[3];
    struct statvfs st;
    DiskUsage();
    long long* getData();
};