#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DIVIDER_FACTOR 1000000.0

using namespace std;

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
public:
    DeviceInformation(string& base_data_dev, const string& additional_data) {
        this->base_data = base_data_dev;
        this->final_data = additional_data;
        this->device_count = 4;
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
};

int main(void) {
    string cpu_device = "/sys/devices/system/cpu/cpu";
    DeviceInformation cpf(cpu_device, "/cpufreq/cpuinfo_cur_freq");
    DeviceInformation cpoi(cpu_device, "/online");
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
}