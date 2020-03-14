#include "CPUFrequencyInformation.h"

CPUFrequencyInformation::CPUFrequencyInformation(string& base_data_dev, const string& additional_data, int dev_count):
    DeviceInformation(base_data_dev, additional_data, dev_count) {
}

int CPUFrequencyInformation::getEachDevData(int& fd) {
    char output[20] = {0,};
    read(fd, output, 19);
    int tmp = atoi(output);
    return tmp;
}

vector<int>& CPUFrequencyInformation::getCPUFrequencyArray(int& counter) {
    counter = device_count; // Super class Derivation.
    device_returned_val.clear();
    registerDev(); // Calling super class from child.
    for (int i = 0; i < device_count; i++) {
        device_returned_val.push_back(getEachDevData(device_info_fd[i]));
    }
    closeFree(); // Calling super class from child.
    return device_returned_val;
}