#include "LoadInnerCore.h"

class LoadManager {
private:
    LoadInnerCore lic[2];
    int counter;
public:
    // First, We need to initiate FIRST Load Inner Core.
    // After designated time passed, initiate second, and calculate percentage of load.
    // After calculating, remove first Load Inner Core, and shift second data to first.
    // After design...
    LoadManager();
    double calculatePercentage();
};