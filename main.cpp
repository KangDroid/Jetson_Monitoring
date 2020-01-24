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

class CPUInformation {
private:
    string base_data;
    string final_data;
    int cpu_count;
    int* cpu_info_fd;
    int* cpu_returned_val;
    void registerCPU() {
        for (int i = 0; i < cpu_count; i++) {
            // TODO: string changed based on mode;
            string tmp = base_data + to_string(i) + final_data;

            cpu_info_fd[i] = open(tmp.c_str(), O_RDONLY, 0644);
            if (cpu_info_fd[i] < 0) {
                // Log based on mode;
                cout << "CPU Frequency FD Verification Failed" << endl;
                cout << "Debugging Info: " << endl;
                cout << "Failed FD --> " << i << endl;
                cout << "Failed FD Value --> " << cpu_info_fd[i] << endl; 
            }
        }
    }
    int getEachCPUData(int& fd) {
        char output[20] = {0,};
        read(fd, output, 19);
        int tmp = atoi(output);
        return tmp;
    }
public:
    CPUInformation(const string& additional_data) {
        this->base_data = "/sys/devices/system/cpu/cpu";
        this->final_data = additional_data;
        this->cpu_count = 4;
        cpu_info_fd = new int[cpu_count];
        cpu_returned_val = new int[cpu_count];
        registerCPU();
    }
    ~CPUInformation() {
        for (int i = 0; i < cpu_count; i++) {
            close(cpu_info_fd[i]);
        }
        delete[] cpu_info_fd;
        delete[] cpu_returned_val;
    }

    int* getCPUDataArray(int& counter) {
        counter = this->cpu_count;
        for (int i = 0; i < cpu_count; i++) {
            cpu_returned_val[i] = getEachCPUData(cpu_info_fd[i]);
        }
        return cpu_returned_val;
    }
};

int main(void) {
    CPUInformation cpf("/cpufreq/cpuinfo_cur_freq");
    CPUInformation cpoi("/online");
    int counter;

    // Online Info
    int* tmp_two = cpoi.getCPUDataArray(counter);
    cout << "----------------" << endl;
    for (int i = 0; i < counter; i++) {
        cout << "CPU " << i + 1 << ": " << ((tmp_two[i]) ? "ON" : "OFF") << endl;
    }
    cout << "----------------" << endl;

    int* tmp = cpf.getCPUDataArray(counter);

    cout << "----------------" << endl;
    for (int i = 0; i < counter; i++) {
        cout << "CPU " << i + 1 << ": " << tmp[i] / DIVIDER_FACTOR << "Ghz" << endl;
    }
    cout << "----------------" << endl;
}