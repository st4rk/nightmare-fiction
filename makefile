TARGET = nfe
LIBS = -lm -lGL -lglfw -lGLEW -lSDL2 -lSDL2_mixer
CC = g++ 
CFLAGS = -std=c++11 -g -Wall 

.PHONY: default all clean

default: $(TARGET)
all: default

SHADERSDIR = shaders
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
OBJECTS += $(patsubst %.cpp, %.o, $(wildcard shaders/*.cpp)) 
OBJECTS += $(patsubst %.cpp, %.o, $(wildcard lib/*.cpp)) 
OBJECTS += $(patsubst %.cpp, %.o, $(wildcard game/mainmenu/*.cpp)) 
OBJECTS += $(patsubst %.cpp, %.o, $(wildcard game/common/*.cpp)) 
OBJECTS += $(patsubst %.cpp, %.o, $(wildcard game/common/AI/*.cpp)) 
OBJECTS += $(patsubst %.cpp, %.o, $(wildcard game/vrmode/*.cpp)) 
OBJECTS += $(patsubst %.cpp, %.o, $(wildcard nf3d/*.cpp))
HEADERS = $(wildcard *.h) $(wildcard shaders/*.h) 

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f game/mainmenu/*.o
	-rm -f game/vrmode/*.o
	-rm -f game/common/*.o	
	-rm -f game/common/AI/*.o
	-rm -f shaders/*.o
	-rm -f nf3d/*.o
	-rm -f lib/*.o
	-rm -f $(TARGET)