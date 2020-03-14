/* TODO: Inheritance */
#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <fstream>

using namespace std;

class DeviceInformation {
protected:
    string base_data;
    string final_data;
    int device_count;
    vector<ifstream*> file_store;
    vector<int> device_returned_val;
    void registerDev();
    void closeFree();
public:
    DeviceInformation(string& base_data_dev, const string& additional_data, int dev_count = 4);
    ~DeviceInformation();
};