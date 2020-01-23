#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DIVIDER_FACTOR 1000000.0

int main(void) {
    int fd_cpu0 = open("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq", O_RDONLY, 0644);
    int fd_cpu1 = open("/sys/devices/system/cpu/cpu1/cpufreq/cpuinfo_cur_freq", O_RDONLY, 0644);
    int fd_cpu2 = open("/sys/devices/system/cpu/cpu2/cpufreq/cpuinfo_cur_freq", O_RDONLY, 0644);
    int fd_cpu3 = open("/sys/devices/system/cpu/cpu3/cpufreq/cpuinfo_cur_freq", O_RDONLY, 0644);

    if (fd_cpu0 == -1 || fd_cpu1 == -1 || fd_cpu2 == -1 || fd_cpu3 == -1) {
        std::cout << "File Open Failed" << std::endl;
        return -1;
    } else {
        std::cout << "File Open Succeed!" << std::endl;
    }

    char output_0[20] = {0,};
    char output_1[20] = {0,};
    char output_2[20] = {0,};
    char output_3[20] = {0,};

    read(fd_cpu0, output_0, 19);
    int freq_cpu0 = atoi(output_0);
    std::cout << "CPU 1: " << (freq_cpu0/DIVIDER_FACTOR) << std::endl;

    //memset (output, 0x00, 20);
    read(fd_cpu1, output_1, 19);
    int freq_cpu1 = atoi(output_1);
    std::cout << "CPU 2: " << freq_cpu1/DIVIDER_FACTOR << std::endl;

    //memset (output, 0x00, 20);
    read(fd_cpu2, output_2, 19);
    int freq_cpu2 = atoi(output_2);
    std::cout << "CPU 3: " << freq_cpu2/DIVIDER_FACTOR << std::endl;

    //memset (output, 0x00, 20);
    read(fd_cpu3, output_3, 19);
    int freq_cpu3 = atoi(output_3);
    std::cout << "CPU 3: " << freq_cpu3/DIVIDER_FACTOR << std::endl;

    close(fd_cpu0);
    close(fd_cpu1);
    close(fd_cpu2);
    close(fd_cpu3);
}