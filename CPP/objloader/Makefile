COMPILER=g++
CFLAGS=-std=c++11
LFLAGS=-lGL -lGLU -lglut
SOURCE=main.cpp
OBJ_D=./obj
BUILD_D=./build
APPNAME=obj


all:
	$(COMPILER) $(CFLAGS) $(SOURCE) -o $(BUILD_D)/$(APPNAME) $(LFLAGS)
excute: all
	$(BUILD_D)/$(APPNAME)