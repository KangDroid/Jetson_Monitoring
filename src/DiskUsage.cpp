#include "DiskUsage.h"
DiskUsage::DiskUsage() {
    // init statvfs
    if (statvfs("/", &st) != 0) {
        // some what failed --> Fallback needed;
    } else {
        diskArray[0] = (long long)st.f_blocks * st.f_bsize / 1024; // total
        diskArray[1] = st.f_bsize * (long long)st.f_bavail / 1024; // Free
        diskArray[2] = (long long)((diskArray[0] - diskArray[1]) / (double)diskArray[0] * 100); // percentage(long)
    }
}

long long* DiskUsage::getData() {
    return this->diskArray;
}