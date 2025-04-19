BIN_DIR := bin
SRC_DIR := source
TARGET := $(BIN_DIR)/main.exe

GXX := g++
CPP_FILES := main.cpp $(SRC_DIR)/*.cpp

$(TARGET) : $(CPP_FILES)
	$(GXX) -cpp $(CPP_FILES) -o $(TARGET)

clean:
	rm -f *.o
