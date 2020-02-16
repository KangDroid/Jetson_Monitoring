CXX=g++
CXXFLAGS= -Wall -O3 -I ../
TARGET=app.out
OBJS=main.o

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -rf ./*.o ./*.out