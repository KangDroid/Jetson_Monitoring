#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
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
    vector<int> device_info_fd;
    vector<int> device_returned_val;
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
    void closeFree() {
        for (int i = 0; i < device_count; i++) {
            close(device_info_fd[i]);
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
        this->device_info_fd.reserve(device_count);
    }
    ~DeviceInformation() {
        for (int i = 0; i < device_count; i++) {
            close(device_info_fd[i]);
        }
    }

    vector<int>& getDevDataArray(int& counter) {
        counter = this->device_count;
        device_returned_val.clear();
        registerDev();
        for (int i = 0; i < device_count; i++) {
            device_returned_val.push_back(getEachDevData(device_info_fd[i]));
        }
        closeFree();
        return device_returned_val;
    }
    void getThermalDescriptor(string* descriptor_store, int& counter) {
        counter = this->device_count;
        registerDev();
        for (int i = 0; i < device_count; i++) {
            descriptor_store[i] = getThermalDescriptor(device_info_fd[i]);
            descriptor_store[i].erase(std::remove(descriptor_store[i].begin(), descriptor_store[i].end(), '\n'), descriptor_store[i].end());
        }
        closeFree();
    }
};

int main(int argc, char* argv[]) {
    // Parse arguments
    /**
     * -c : Continously show information(Default interval: 2 seconds)
     * -n : Set show interval
     */
    string* arguments_list = new string[argc];
    int show_interval = 2;
    bool continous_show = false;

    // Skip argv[0] because it contains the filename itself.
    for (int i = 1; i < argc; i++) {
        arguments_list[i] = string(argv[i]);

        if (arguments_list[i] == "-c") {
            continous_show = true;
        }

        if (arguments_list[i] == "-n") {
            i++;
            arguments_list[i] = string(argv[i]);
            show_interval = atoi(arguments_list[i].c_str());
        }
    }

    cout << "Continous Show: " << continous_show << endl;
    cout << "Interval: " << show_interval << endl;

    string cpu_device = "/sys/devices/system/cpu/cpu";
    string thermal_device = "/sys/devices/virtual/thermal/thermal_zone";

    DeviceInformation cpf(cpu_device, "/cpufreq/cpuinfo_cur_freq");
    DeviceInformation cpoi(cpu_device, "/online");

    DeviceInformation thermal_dev_desc(thermal_device, "/type", 6);
    DeviceInformation thermal_dev(thermal_device, "/temp", 6);
    int counter;

    while (continous_show == true) {
        // Online Info
        system("clear && printf '\e[3J'");
        vector<int> tmp_two = cpoi.getDevDataArray(counter);
        cout << "----------------" << endl;
        for (int i = 0; i < counter; i++) {
            cout << "CPU " << i + 1 << ": " << ((tmp_two[i]) ? "ON" : "OFF") << endl;
        }
        cout << "----------------" << endl;

        vector<int> tmp = cpf.getDevDataArray(counter);

        cout << "----------------" << endl;
        for (int i = 0; i < counter; i++) {
            cout << "CPU " << i + 1 << ": " << tmp[i] / DIVIDER_FACTOR << "Ghz" << endl;
        }
        cout << "----------------" << endl;

        // Thermal Information:
        string thermal_information[6];
        vector<int> tmp_three = thermal_dev.getDevDataArray(counter);
        thermal_dev_desc.getThermalDescriptor(thermal_information, counter);
        cout << "----------------" << endl;
        for (int i = 0; i < counter; i++) {
            cout << thermal_information[i] << ": " << tmp_three[i]/THERM_DIVIDER_FACTOR << endl;
        }
        cout << "----------------" << endl;
        sleep(show_interval);
    }

    delete[] arguments_list;
}