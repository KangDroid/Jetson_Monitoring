#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DIVIDER_FACTOR 1000000.0
#define THERM_DIVIDER_FACTOR 1000.0

using namespace std;

/* TODO: Inheritance */

class DeviceInformation {
private:
    string base_data;
    string final_data;
    int device_count;
    int* device_info_fd;
    int* device_returned_val;
    void registerDev() {
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
    int getEachDevData(int& fd) {
        char output[20] = {0,};
        read(fd, output, 19);
        int tmp = atoi(output);
        return tmp;
    }
    string getThermalDescriptor(int& fd) {
        char output[40] = {0,};
        read(fd, output, 39);
        string t(output);
        return t;
    }
public:
    DeviceInformation(string& base_data_dev, const string& additional_data, int dev_count = 4) {
        this->base_data = base_data_dev;
        this->final_data = additional_data;
        this->device_count = dev_count;
        device_info_fd = new int[device_count];
        device_returned_val = new int[device_count];
        registerDev();
    }
    ~DeviceInformation() {
        for (int i = 0; i < device_count; i++) {
            close(device_info_fd[i]);
        }
        delete[] device_info_fd;
        delete[] device_returned_val;
    }

    int* getDevDataArray(int& counter) {
        counter = this->device_count;
        for (int i = 0; i < device_count; i++) {
            device_returned_val[i] = getEachDevData(device_info_fd[i]);
        }
        return device_returned_val;
    }
    void getThermalDescriptor(string* descriptor_store, int& counter) {
        counter = this->device_count;
        for (int i = 0; i < device_count; i++) {
            descriptor_store[i] = getThermalDescriptor(device_info_fd[i]);
            descriptor_store[i].erase(std::remove(descriptor_store[i].begin(), descriptor_store[i].end(), '\n'), descriptor_store[i].end());
        }
    }
};

int main(void) {
    string cpu_device = "/sys/devices/system/cpu/cpu";
    string thermal_device = "/sys/devices/virtual/thermal/thermal_zone";

    DeviceInformation cpf(cpu_device, "/cpufreq/cpuinfo_cur_freq");
    DeviceInformation cpoi(cpu_device, "/online");

    DeviceInformation thermal_dev_desc(thermal_device, "/type", 6);
    DeviceInformation thermal_dev(thermal_device, "/temp", 6);
    int counter;

    // Online Info
    int* tmp_two = cpoi.getDevDataArray(counter);
    cout << "----------------" << endl;
    for (int i = 0; i < counter; i++) {
        cout << "CPU " << i + 1 << ": " << ((tmp_two[i]) ? "ON" : "OFF") << endl;
    }
    cout << "----------------" << endl;

    int* tmp = cpf.getDevDataArray(counter);

    cout << "----------------" << endl;
    for (int i = 0; i < counter; i++) {
        cout << "CPU " << i + 1 << ": " << tmp[i] / DIVIDER_FACTOR << "Ghz" << endl;
    }
    cout << "----------------" << endl;

    // Thermal Information:
    string thermal_information[6];
    int* tmp_three = thermal_dev.getDevDataArray(counter);
    thermal_dev_desc.getThermalDescriptor(thermal_information, counter);
    cout << "----------------" << endl;
    for (int i = 0; i < counter; i++) {
        cout << thermal_information[i] << ": " << tmp_three[i]/THERM_DIVIDER_FACTOR << endl;
    }
    cout << "----------------" << endl;
}