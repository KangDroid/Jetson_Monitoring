#include "CPUThermalInformation.h"

CPUThermalInformation::CPUThermalInformation(string& base_data_dev, const string& additional_data, int dev_count):
    DeviceInformation(base_data_dev, additional_data, dev_count) {
}

/*void CPUThermalInformation::getThermalDescriptor(string* descriptor_store, int& counter) {
    counter = this->device_count;
    registerDev();
    for (int i = 0; i < device_count; i++) {
        descriptor_store[i] = getThermalDescriptor(device_info_fd[i]);
        descriptor_store[i].erase(std::remove(descriptor_store[i].begin(), descriptor_store[i].end(), '\n'), descriptor_store[i].end());
    }
    closeFree();
}

string CPUThermalInformation::getThermalDescriptor(int& fd) {
    char output[40] = {0,};
    read(fd, output, 39);
    string t(output);
    return t;
}*/

vector<int>& CPUThermalInformation::getThermalArray(int& counter) {
    counter = device_count; // Super class Derivation.
    device_returned_val.clear();
    registerDev(); // Calling super class from child.
    for (int i = 0; i < device_count; i++) {
        device_returned_val.push_back(getEachDevData(file_store[i]));
    }
    closeFree(); // Calling super class from child.
    return device_returned_val;
}

int CPUThermalInformation::getEachDevData(ifstream* fd) {
    int tmp = 0;
    char test[20] = {0,};
    if (fd->is_open()) {
        fd->read(test, 19);
        tmp = atoi(test);
    }
    return tmp;
}