#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>

using namespace std;

class LoadInnerCore {
private:
    ifstream filedirectory;
    int total_jiffles;
    int total_work_jiffles;
    string tmp;
public:
    void init();
    int& getTotalJiffle();
    int& getTotalWorkJiffle();
    void setTotalJiffle(int& totjif);
    void setTotalWorkJiffle(int& totworkjif);
};