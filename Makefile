use_jetson:
	cp config/jetson_nano/Configuration.h Configuration.h

use_rpi:
	cp config/rpi/Configuration.h Configuration.h

rpi: use_rpi main.o
	g++ -o monitor main.o
	rm -rf *.o

nano: use_jetson main.o
	g++ -o monitor main.o
	rm -rf *.o

clean:
	rm -rf *.o
	rm -rf monitor
	cp config/default/Configuration.h Configuration.h