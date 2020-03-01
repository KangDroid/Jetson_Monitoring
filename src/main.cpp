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

// Proc-Related
#include "ProcReader.h"

// Core
#include "CPUFrequencyInformation.h"
#include "CPUThermalInformation.h"

// Disk Usage
#include "DiskUsage.h"

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
     * -s : Streaming Directory
     */

    // Default Settings
    int show_interval = 2;
    bool continous_show = false;
    string streaming_dir = "/var/www/html/cpu_log";

    // Skip argv[0] because it contains the filename itself.
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-c")) {
            continous_show = true;
        }

        if (!strcmp(argv[i], "-n")) {
            i++;
            show_interval = atoi(argv[i]);
        }

        if (!strcmp(argv[i], "-s")) {
            i++;
            streaming_dir = string(argv[i]);
        }
    }

    // OFSTREAM
    ofstream file(streaming_dir);

    // Disk Usage
    DiskUsage disk_usage;

#ifdef DEBUG
    cout << "Continous Show: " << continous_show << endl;
    cout << "Interval: " << show_interval << endl;
#endif

#ifdef ENABLE_LOAD
    string load_readfile = "/proc/loadavg";
    ProcReader prload(load_readfile);
#endif

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
        file.open(streaming_dir);

        /**
         * First line ~ 4th line will be CPU Information
         */
#ifndef IS_RASPBIAN
        vector<int> tmp_two = cpoi.getCPUFrequencyArray(counter);
        for (int i = 0; i < counter; i++) {
            file << "CPU " << i + 1 << ": " << ((tmp_two[i]) ? "ON" : "OFF") << endl;
        }
#endif

        vector<int> tmp = cpf.getCPUFrequencyArray(counter);

        for (int i = 0; i < counter; i++) {
            file << tmp[i] / DIVIDER_FACTOR << endl;
        }

#ifndef IS_RASPI
        // Thermal Information:
        string thermal_information[6];
#else
        string thermal_information[2];
#endif
        vector<int> tmp_three = thermal_dev.getThermalArray(counter);
        thermal_dev_desc.getThermalDescriptor(thermal_information, counter);
        for (int i = 0; i < counter; i++) {
            file << tmp_three[i]/THERM_DIVIDER_FACTOR << endl;
        }

#ifdef ENABLE_LOAD
        file << prload.readProcFile();
#endif
        // Disk Usage Information
        long long* diskData = disk_usage.getData();
        file << diskData[2] << endl;

        if (!continous_show) {
            break;
        }
        sleep(show_interval);
    }
}