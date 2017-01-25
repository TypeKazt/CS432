LDLIBS = -lglut -lGLEW -lGL -lGLU

FNAME = helloWorld432

CXXINCS = -I../../include

INIT_SHADER = ./InitShader.cpp
INIT_SHADER_OBJ = ./InitShader.o

EXAMPLELIST = $(wildcard *.cpp)
TARGETS = $(basename $(EXAMPLELIST))
DEPS = $(TARGETS:=.o)

all: $(FNAME:=.o) $(TARGETS)
	g++ $(DEPS) $(LDLIBS) -o $(FNAME)

$(FNAME:=.o): $(FNAME:=.cpp)
	g++ -c $(FNAME:=.cpp) -o $(FNAME:=.o) -O2 $(CXXINCS)
	
$(TARGETS): $(INIT_SHADER_OBJ)
	g++ -c $@.cpp -o $@.o -O2 $(CXXINCS)
	
	
$(INIT_SHADER_OBJ): $(INIT_SHADER)
	g++ -c -Wall $(INIT_SHADER) -o $(INIT_SHADER_OBJ) -O2 $(CXXINCS)

clean:
	rm *.o
	
cleanall:
	rm *.o
