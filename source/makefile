#EI="/Users/Gonzalo/github/nuCD/EI/"

CC = g++
CFLAGS = -g -Wall
TARGET = nucd
MAIN = nuCD.cc

###### include dirs
G4 = -I/Applications/Geant4/install/include/Geant4
this = -I$(PWD)

#### SUBDOLFERS SOURCES
ACT  = action/*.cc
CORE = core/*.cc
MGR  = core/manager/*.cc
GEN  = generation/*.cc
GEO  = geometry/*.cc
#SENS = geometry/sensors/*.cc
MAT  = materials/*.cc
#PHYS = physics/*.cc

#SOURCES = $(MAIN) $(ACT) $(CORE) $(MGR) $(GEN) $(GEO) $(SENS) $(MAT) $(PHYS)
SOURCES = $(MAIN) $(ACT) $(MGR) $(CORE) $(GEN) $(GEO) $(MAT)

all: $(TARGET)

$(TARGET): nuCD.cc
	$(CC) $(CFLAGS) $(this) `root-config --cflags --glibs --libs` $(G4) `geant4-config --libs` `nuei-config --include --libdir --libs` $(SOURCES) -o $(TARGET)

clean:
	$(RM) $(TARGET) *.o
