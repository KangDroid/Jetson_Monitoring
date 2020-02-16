#include "DeviceInformation.h"

class CPUFrequencyInformation: public DeviceInformation {
public:
    CPUFrequencyInformation(string& base_data_dev, const string& additional_data, int dev_count = 4);
    int getEachDevData(int& fd);
    vector<int>& getCPUFrequencyArray(int& counter);
};