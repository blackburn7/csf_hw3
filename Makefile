CXX = g++
CXXFLAGS = -g -Wall -std=c++17
TARGET = csim
SRCS = main.cpp cache.cpp
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

zip:
	zip solution.zip cache.h cache.cpp main.cpp README.txt Makefile