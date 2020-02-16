/* TODO: Inheritance */

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

using namespace std;

class DeviceInformation {
private:
    string base_data;
    string final_data;
    int device_count;
    vector<int> device_info_fd;
    vector<int> device_returned_val;
    void registerDev();
    void closeFree();
    int getEachDevData(int& fd);
    string getThermalDescriptor(int& fd);
public:
    DeviceInformation(string& base_data_dev, const string& additional_data, int dev_count = 4);
    ~DeviceInformation();

    vector<int>& getDevDataArray(int& counter);
    void getThermalDescriptor(string* descriptor_store, int& counter);
};