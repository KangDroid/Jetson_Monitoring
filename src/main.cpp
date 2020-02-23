#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fstream>

#include <unistd.h>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Core
#include "CPUFrequencyInformation.h"
#include "CPUThermalInformation.h"

// User-Defined Configuration.h
#include "Configuration.h"

using namespace std;

// TODO: Clear out Main function, and move those parse-execution to
//       somewhat class.

int main(int argc, char* argv[]) {
    // Parse arguments
    /**
     * -c : Continously show information(Default interval: 2 seconds)
     * -n : Set show interval
     */

    // Default Settings
    int show_interval = 2;
    bool continous_show = false;

    // Skip argv[0] because it contains the filename itself.
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-c")) {
            continous_show = true;
        }

        if (!strcmp(argv[i], "-n")) {
            i++;
            show_interval = atoi(argv[i]);
        }
    }

    // OFSTREAM
    ofstream file("cpu_log");

    cout << "Continous Show: " << continous_show << endl;
    cout << "Interval: " << show_interval << endl;

    string cpu_device = "/sys/devices/system/cpu/cpu";
    string thermal_device = "/sys/devices/virtual/thermal/thermal_zone";

    CPUFrequencyInformation cpf(cpu_device, "/cpufreq/cpuinfo_cur_freq");
#ifndef IS_RASPBIAN
    CPUFrequencyInformation cpoi(cpu_device, "/online");
#endif

#ifndef IS_RASPI
    CPUThermalInformation thermal_dev_desc(thermal_device, "/type", 6);
    CPUThermalInformation thermal_dev(thermal_device, "/temp", 6);
#else
    CPUThermalInformation thermal_dev_desc(thermal_device, "/type", 1);
    CPUThermalInformation thermal_dev(thermal_device, "/temp", 1);
#endif
    int counter;

    // File Streaming
    while (true) {
        if (file.is_open()) {
            file.close();
        }
        file.open("cpu_log");

#ifndef IS_RASPBIAN
        vector<int> tmp_two = cpoi.getCPUFrequencyArray(counter);
        file << "----------------" << endl;
        for (int i = 0; i < counter; i++) {
            file << "CPU " << i + 1 << ": " << ((tmp_two[i]) ? "ON" : "OFF") << endl;
        }
        file << "----------------" << endl;
#endif

        vector<int> tmp = cpf.getCPUFrequencyArray(counter);

        file << "----------------" << endl;
        for (int i = 0; i < counter; i++) {
            file << "CPU " << i + 1 << ": " << tmp[i] / DIVIDER_FACTOR << "Ghz" << endl;
        }
        file << "----------------" << endl;

#ifndef IS_RASPI
        // Thermal Information:
        string thermal_information[6];
#else
        string thermal_information[2];
#endif
        vector<int> tmp_three = thermal_dev.getThermalArray(counter);
        thermal_dev_desc.getThermalDescriptor(thermal_information, counter);
        file << "----------------" << endl;
        for (int i = 0; i < counter; i++) {
            file << thermal_information[i] << ": " << tmp_three[i]/THERM_DIVIDER_FACTOR << endl;
        }
        file << "----------------" << endl;
        if (!continous_show) {
            break;
        }
        sleep(show_interval);
    }
}