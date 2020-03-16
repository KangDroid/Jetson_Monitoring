// Proc-Related
#include "LoadManager.h"

// Core
#include "CPUFrequencyInformation.h"
#include "CPUThermalInformation.h"

// Disk Usage
#include "DiskUsage.h"

// Uptime
#include "SysInfoReader.h"

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
    LoadManager lm;
#endif

    string cpu_device = "/sys/devices/system/cpu/cpu";
    string thermal_device = "/sys/devices/virtual/thermal/thermal_zone";

#ifdef IS_DTOP
    CPUFrequencyInformation cpf(cpu_device, "/cpufreq/scaling_cur_freq", 12);
#endif

#ifdef IS_RASPBIAN
    CPUFrequencyInformation cpf(cpu_device, "/cpufreq/cpuinfo_cur_freq");
#endif

#ifdef IS_JETSON
    CPUFrequencyInformation cpoi(cpu_device, "/online");
#endif

#ifdef IS_JETSON
    CPUThermalInformation thermal_dev_desc(thermal_device, "/type", 6);
    CPUThermalInformation thermal_dev(thermal_device, "/temp", 6);
#endif

#if defined(IS_DTOP) || defined(IS_RASPI)
    CPUThermalInformation thermal_dev_desc(thermal_device, "/type", 1);
    CPUThermalInformation thermal_dev(thermal_device, "/temp", 1);
#endif

    SysInfoReader sir;
    int counter;

    // File Streaming
    while (true) {
        string output_str = "";
        /**
         * First line ~ 4th line will be CPU Information
         */
#ifdef IS_JETSON
        vector<int> tmp_two = cpoi.getCPUFrequencyArray(counter);
        for (int i = 0; i < counter; i++) {
            file << "CPU " << i + 1 << ": " << ((tmp_two[i]) ? "ON" : "OFF") << endl;
        }
#endif

        vector<int> tmp = cpf.getCPUFrequencyArray(counter);

        for (int i = 0; i < counter; i++) {
            if (i == counter - 1) {
                output_str.append(to_string(tmp[i] / DIVIDER_FACTOR) + "\n");
            } else {
                output_str.append(to_string(tmp[i] / DIVIDER_FACTOR) + " ");
            }
        }

#ifdef IS_JETSON
        // Thermal Information:
        string thermal_information[6];
#endif

#if defined(IS_RASPI) || defined(IS_DTOP)
        string thermal_information[2];
#endif
        vector<int> tmp_three = thermal_dev.getThermalArray(counter);
        //thermal_dev_desc.getThermalDescriptor(thermal_information, counter);
        for (int i = 0; i < counter; i++) {
            output_str.append(to_string(tmp_three[i]/THERM_DIVIDER_FACTOR) + "\n");
        }

#ifdef ENABLE_LOAD
        output_str.append(to_string(lm.calculatePercentage()) + "\n");
#endif
        // Disk Usage Information
        long long* diskData = disk_usage.getData();
        output_str.append(to_string(diskData[2]) + "\n");

        output_str.append(to_string(sir.getUptime()) + "\n");

        // Free Ram Percentage
        double freeRamPctg = sir.getFreeRamPercentage();
        output_str.append(to_string(freeRamPctg) + "\n");

        file.open(streaming_dir);
        cout << "Start" << endl;
        // Write to file
        file << output_str;
        file.close();
        cout << "end" << endl;

        if (!continous_show) {
            break;
        }
        sleep(show_interval);
    }
}