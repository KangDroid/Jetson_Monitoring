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

class CPUFrequencyInformation {
private:
    int cpu_count;
    int* cpu_freq_fd;
    double* cpu_freq_val;

    void registerCPUFreq() {
        for (int i = 0; i < cpu_count; i++) {
            string tmp = "/sys/devices/system/cpu/cpu" + to_string(i) +"/cpufreq/cpuinfo_cur_freq";
            cpu_freq_fd[i] = open(tmp.c_str(), O_RDONLY, 0644);
            if (cpu_freq_fd[i] < 0) {
                cout << "CPU Frequency FD Verification Failed" << endl;
                cout << "Debugging Info: " << endl;
                cout << "Failed FD --> " << i << endl;
                cout << "Failed FD Value --> " << cpu_freq_fd[i] << endl; 
            }
        }
    }

    double getEachCPUFreq(int& fd) {
        char output[20] = {0,};
        read(fd, output, 19);
        int tmp = atoi(output);
        return (tmp / DIVIDER_FACTOR);
    }
public:
    CPUFrequencyInformation() {
        this->cpu_count = 4;
        cpu_freq_fd = new int[cpu_count];
        cpu_freq_val = new double[cpu_count];
        registerCPUFreq();
    }
    ~CPUFrequencyInformation() {
        for (int i = 0; i < cpu_count; i++) {
            close(cpu_freq_fd[i]);
        }
        delete[] cpu_freq_fd;
        delete[] cpu_freq_val;
    }
    double* getCPUFreqArray(int& counter) {
        counter = this->cpu_count;
        for (int i = 0; i < cpu_count; i++) {
            cpu_freq_val[i] = getEachCPUFreq(cpu_freq_fd[i]);
        }
        return cpu_freq_val;
    }
};

class CPUOnlineInformation {
private:
    int cpu_count;
    int* cpu_online_fd;
    bool* cpu_online_val;
    void registerCPUOnline() {
        for (int i = 0; i < cpu_count; i++) {
            string tmp = "/sys/devices/system/cpu/cpu" + to_string(i) +"/online";
            cpu_online_fd[i] = open(tmp.c_str(), O_RDONLY, 0644);
            if (cpu_online_fd[i] < 0) {
                cout << "CPU Online FD Verification Failed" << endl;
                cout << "Debugging Info: " << endl;
                cout << "Failed FD --> " << i << endl;
                cout << "Failed FD Value --> " << cpu_online_fd[i] << endl; 
            }
        }
    }

    bool getEachOnline(int& fd) {
        char output[20] = {0,};
        read(fd, output, 19);
        bool tmp = (output[0] == '1') ? true : false;
        return tmp;
    }
public:
    CPUOnlineInformation() {
        this->cpu_count = 4;
        cpu_online_fd = new int[cpu_count];
        cpu_online_val = new bool[cpu_count];
        registerCPUOnline();
    }
    ~CPUOnlineInformation() {
        for (int i = 0; i < cpu_count; i++) {
            close(cpu_online_fd[i]);
        }
        delete[] cpu_online_fd;
        delete[] cpu_online_val;
    }
    bool* getCPUOnlineArray(int& counter) {
        counter = this->cpu_count;
        for (int i = 0; i < cpu_count; i++) {
            cpu_online_val[i] = getEachOnline(cpu_online_fd[i]);
        }
        return cpu_online_val;
    }
};

int main(void) {
    CPUFrequencyInformation cpf;
    CPUOnlineInformation cpoi;
    int counter;
    double* tmp = cpf.getCPUFreqArray(counter);

    cout << "----------------" << endl;
    for (int i = 0; i < counter; i++) {
        cout << "CPU " << i + 1 << ": " << tmp[i] << "Ghz" << endl;
    }
    cout << "----------------" << endl;

    // Online Info
    bool* tmp_two = cpoi.getCPUOnlineArray(counter);
    cout << "----------------" << endl;
    for (int i = 0; i < counter; i++) {
        cout << "CPU " << i + 1 << ": " << tmp_two[i] << endl;
    }
    cout << "----------------" << endl;
}