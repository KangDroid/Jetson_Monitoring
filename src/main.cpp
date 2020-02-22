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

    cout << "Continous Show: " << continous_show << endl;
    cout << "Interval: " << show_interval << endl;

    string cpu_device = "/sys/devices/system/cpu/cpu";
    string thermal_device = "/sys/devices/virtual/thermal/thermal_zone";

    CPUFrequencyInformation cpf(cpu_device, "/cpufreq/cpuinfo_cur_freq");
    CPUFrequencyInformation cpoi(cpu_device, "/online");

#ifndef IS_RASPI
    CPUThermalInformation thermal_dev_desc(thermal_device, "/type", 6);
    CPUThermalInformation thermal_dev(thermal_device, "/temp", 6);
#else
    CPUThermalInformation thermal_dev_desc(thermal_device, "/type", 1);
    CPUThermalInformation thermal_dev(thermal_device, "/temp", 1);
#endif
    int counter;

    while (continous_show == true) {
        // Online Info
        system("clear && printf '\e[3J'");
        vector<int> tmp_two = cpoi.getCPUFrequencyArray(counter);
        cout << "----------------" << endl;
        for (int i = 0; i < counter; i++) {
            cout << "CPU " << i + 1 << ": " << ((tmp_two[i]) ? "ON" : "OFF") << endl;
        }
        cout << "----------------" << endl;

        vector<int> tmp = cpf.getCPUFrequencyArray(counter);

        cout << "----------------" << endl;
        for (int i = 0; i < counter; i++) {
            cout << "CPU " << i + 1 << ": " << tmp[i] / DIVIDER_FACTOR << "Ghz" << endl;
        }
        cout << "----------------" << endl;

#ifndef IS_RASPI
        // Thermal Information:
        string thermal_information[6];
#else
        string thermal_information[2];
#endif
        vector<int> tmp_three = thermal_dev.getThermalArray(counter);
        thermal_dev_desc.getThermalDescriptor(thermal_information, counter);
        cout << "----------------" << endl;
        for (int i = 0; i < counter; i++) {
            cout << thermal_information[i] << ": " << tmp_three[i]/THERM_DIVIDER_FACTOR << endl;
        }
        cout << "----------------" << endl;
        sleep(show_interval);
    }
}