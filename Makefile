CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC = src/main.cpp \
      src/filesystem.cpp \
      src/inode.cpp

TARGET = securevfs

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
