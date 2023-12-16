.PHONY: clean NUKE

all: DSE

DSE: 431project.cpp 431project.h 431projectUtils.cpp 431projectUtils.h YOURCODEHERE.cpp
	g++ -static-libstdc++ -O3 431project.cpp 431projectUtils.cpp YOURCODEHERE.cpp -lm -o DSE

clean:
	-rm DSE

NUKE:
	-rm DSE; rm -rf rawProjectOutputData summaryfiles logs