#Bin
OUTPUT=./bin/exe

#Include path
IDIR=-Iinclude -Iexternal/lib/GoogleBenchmark/include -I../include 

#Cpp version
CPP_VERSION=-std=gnu++17

#Relase or debug option
CXX_DEBUG=-Og $(CPP_VERSION) -g -W -Wall -pg -no-pie -MMD -Wno-unknown-pragmas $(IDIR)
CXX_BUILD=-O3 $(CPP_VERSION) -DNDEBUG -MMD -Wno-unknown-pragmas $(IDIR)

C_DEBUG=-Og -g -pg -no-pie -MMD -W -Wall -Wno-unknown-pragmas $(IDIR)
C_BUILD=-O3 -DNDEBUG -MMD -Wno-unknown-pragmas $(IDIR)

#Valgrind flag
#VFLAG=--leak-check=yes
VFLAG=--leak-check=full --show-leak-kinds=all

#Lib
LIB_GOOGLE_BENCHMARCK = external/lib/GoogleBenchmark/src/libbenchmark.a
LDLIBS= $(LIB_GOOGLE_BENCHMARCK)

#Cpp and C wildcard
SRCPPS=$(wildcard src/*.cpp) 
SRCS=$(wildcard src/*.c) 
OBJS=$(SRCS:.c=.o) $(SRCPPS:.cpp=.o)

.PHONY: run

all: $(OUTPUT)

multi :
	mkdir -p bin
	make -j all

-include $(OBJS:.o=.d)

%.o: %.cpp
	g++ -c $(CXX_BUILD) $< -o $@

%.o: %.c
	gcc -c $(C_BUILD) $< -o $@

$(OUTPUT): $(OBJS)
	mkdir -p bin
	g++ -pg -no-pie $^  $(LDLIBS) -lpthread -o $@

run : $(OUTPUT) 
	./$(OUTPUT)

#debugger. Use "run" to start
gdb :
	make all 
	gdb $(OUTPUT)

#display function stats
gprof :
	gprof $(OUTPUT) gmon.out > output.txt

#display leak
leak :
	make all
	valgrind $(OUTPUT)

#display leak detail
leakFull :
	make all 
	valgrind $(VFLAG) $(OUTPUT)

cleanAll:
	rm -f $(OBJS) $(OBJS:.o=.d) $(OUTPUT)

#SRC_FILES = $(filter-out src/bar.cpp, $(wildcard src/*.cpp))
clean :
	rm -f $(filter-out $(EXCLUDE) $(EXCLUDE:.o=.d),$(OBJS:.o=.d) $(OBJS))
