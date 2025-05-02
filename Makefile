CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = project2
SRCS = main.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) *.o
