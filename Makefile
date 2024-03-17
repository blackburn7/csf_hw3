CXX = g++
CXXFLAGS = -g -Wall -std=c++17

TARGET = csim



$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)
	

zip: 
	zip solution.zip cache.h cache.cpp main.cpp README.txt Makefile

clean :
	rm -f $(TARGET)