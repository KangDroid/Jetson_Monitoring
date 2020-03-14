#include "DeviceInformation.h"

class CPUThermalInformation : public DeviceInformation {
public:
    CPUThermalInformation(string& base_data_dev, const string& additional_data, int dev_count = 4);
    //void getThermalDescriptor(string* descriptor_store, int& counter);
    //string getThermalDescriptor(int& fd);
    vector<int>& getThermalArray(int& counter);
    vector<int> retValue;
    int getEachDevData(ifstream* fd);
};