CXX=g++
CXXFLAGS= -Wall -O3 -I ../ -I ../include
TARGET=app.out
OBJS= LoadManager.o\
	LoadInnerCore.o\
	SysInfoReader.o\
	DiskUsage.o\
	CPUThermalInformation.o\
	CPUFrequencyInformation.o\
	DeviceInformation.o\
	main.o

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -rf ./*.o ./*.out