LDLIBS = -lglut -lGLEW -lGL -lGLU

FNAME = main

CXXINCS = -I../../include

INIT_SHADER = ./InitShader.cpp
INIT_SHADER_OBJ = ./InitShader.o

EXAMPLELIST = $(wildcard *.cpp)
TARGETS = $(basename $(EXAMPLELIST))
DEPS = $(TARGETS:=.o)

all: $(FNAME:=.o) $(TARGETS)
	g++ $(DEPS) $(LDLIBS) -o $(FNAME) 


$(TARGETS): $(INIT_SHADER_OBJ)
	g++ -c $@.cpp -o $@.o -ggdb
	
clean:
	rm *.o
	
cleanall:
	rm *.o
