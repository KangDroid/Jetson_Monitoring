#include "DeviceInformation.h"

void DeviceInformation::registerDev() {
    for (int i = 0; i < device_count; i++) {
        // TODO: string changed based on mode;
        string tmp = base_data + to_string(i) + final_data;
        device_info_fd[i] = open(tmp.c_str(), O_RDONLY, 0644);
        if (device_info_fd[i] < 0) {
            // Log based on mode;
            cout << "CPU Frequency FD Verification Failed" << endl;
            cout << "Debugging Info: " << endl;
            cout << "Failed FD --> " << i << endl;
            cout << "Failed FD Value --> " << device_info_fd[i] << endl; 
        }
    }
}

void DeviceInformation::closeFree() {
    for (int i = 0; i < device_count; i++) {
        close(device_info_fd[i]);
    }
}

DeviceInformation::DeviceInformation(string& base_data_dev, const string& additional_data, int dev_count) {
    this->base_data = base_data_dev;
    this->final_data = additional_data;
    this->device_count = dev_count;
    this->device_info_fd.reserve(device_count);
}
DeviceInformation::~DeviceInformation() {
    for (int i = 0; i < device_count; i++) {
        close(device_info_fd[i]);
    }
}