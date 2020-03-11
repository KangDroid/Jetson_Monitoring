#include "LoadManager.h"

LoadManager::LoadManager() {
    this->counter = 0;
}

double LoadManager::calculatePercentage() {
    double retval = 0.0;
    if (counter == 0) {
        lic[0].init();
        retval = 0.0;
    } else {
        // Init second one.
        lic[1].init();

        // Calculate
        int work_period = lic[1].getTotalWorkJiffle() - lic[0].getTotalWorkJiffle();
        int total_period = lic[1].getTotalJiffle() - lic[0].getTotalJiffle();
        retval = ((double)work_period / total_period) * 100;
        
        // Transfer data from lic 1 to lic 0
        lic[0].setTotalJiffle(lic[1].getTotalJiffle());
        lic[0].setTotalWorkJiffle(lic[1].getTotalWorkJiffle());
    }
    counter++;
    return retval;
}