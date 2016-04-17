
CC = g++
CFLAGS = -g -Wall
TARGET = nuCD

all: $(TARGET)

$(TARGET): macro.C
#	  $(CC) $(CFLAGS) `root-config --cflags --glibs --libs` `irene-config --include --libdir --libs` $(SOURCES) -o $(TARGET)
	  $(CC) $(CFLAGS) `root-config --cflags --glibs --libs` `nuei-config --include --libdir --libs`  $(SOURCES) -o $(TARGET)

clean:
	$(RM) $(TARGET) *.o
