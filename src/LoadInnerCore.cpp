#include "LoadInnerCore.h"

void LoadInnerCore::init() {
    // Must Clear value so it won't use it again.
    this->total_jiffles = 0;
    this->total_work_jiffles = 0;

    // Open /proc/stat
    this->filedirectory.open("/proc/stat");

    // Abandon first col(CPU)
    filedirectory >> tmp;

    // Get Total Jiffles, total work jiffles.
    for (int i = 0; i < 10; i++) {
        filedirectory >> tmp;
        if (i < 3) {
            total_work_jiffles += stoi(tmp);
        }
        total_jiffles += stoi(tmp);
    }

    // Close
    this->filedirectory.close();
}

int& LoadInnerCore::getTotalJiffle() {
    return this->total_jiffles;
}

int& LoadInnerCore::getTotalWorkJiffle() {
    return this->total_work_jiffles;
}

void LoadInnerCore::setTotalJiffle(int& totjif) {
    this->total_jiffles = totjif;
}

void LoadInnerCore::setTotalWorkJiffle(int& totworkjif) {
    this->total_work_jiffles = totworkjif;
}