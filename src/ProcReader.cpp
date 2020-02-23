#include "ProcReader.h"

ProcReader::ProcReader(string& str) {
    this->read_dest = str;
}

void ProcReader::registerFD() {
    // init
    this->device_open = open(read_dest.c_str(), O_RDONLY, 0644);
    if (this->device_open < 0) {
        cout << "FD Verification Failed" << endl;
    }
}

string ProcReader::readProcFile() {
    // Read
    char tmpoutput[40] = {0,};
    registerFD();
    read(this->device_open, tmpoutput, 39);
    close(this->device_open);
    return string(tmpoutput);
}

ProcReader::~ProcReader() {
    close(this->device_open);
}