CXX = g++
CXXFLAGS = -std=c++11 -Wall -pthread -I/Users/keina/cpp-libs/boost_1_86_0

SRC = src/main.cpp src/Server.cpp src/HttpResponse.cpp
OBJ = $(SRC:.cpp=.o)
INCLUDE = -Iinclude

TARGET = server

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) -lpthread

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
