#include "DeviceInformation.h"

void DeviceInformation::registerDev() {
    for (int i = 0; i < device_count; i++) {
        // TODO: string changed based on mode;
        string tmp = base_data + to_string(i) + final_data;
        ifstream* tmpObject = new ifstream(tmp);
        file_store[i] = tmpObject;
    }
}

void DeviceInformation::closeFree() {
    for (int i = 0; i < device_count; i++) {
        if (file_store[i]->is_open()) {
            file_store[i]->close();
        }
        delete file_store[i];
    }
}

DeviceInformation::DeviceInformation(string& base_data_dev, const string& additional_data, int dev_count) {
    this->base_data = base_data_dev;
    this->final_data = additional_data;
    this->device_count = dev_count;
    this->file_store.reserve(device_count);
}
DeviceInformation::~DeviceInformation() {
    for (int i = 0; i < device_count; i++) {
        if (file_store[i]->is_open()) {
            file_store[i]->close();
        }
    }
}