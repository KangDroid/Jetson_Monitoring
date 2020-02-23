#include "DeviceInformation.h"
class ProcReader {
private:
    string read_dest;
    int device_open;
public:
    ProcReader(string& read_dir);
    void registerFD();
    string readProcFile();
    ~ProcReader();
};