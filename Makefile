IDIR = /includes

SRCDIR=src
CXX=g++
CXXFLAGS= -I. -std=c++14
CXXLIBS = -lGL -lglfw -ldl

DEPS = 

_OBJECTS = main.o glad.o Shader.o Camera.o
OBJECTS = $(patsubst %,$(SRCDIR)/%,$(_OBJECTS))

TARGET = main.out

$(SRCDIR)/%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(TARGET) : $(OBJECTS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(CXXLIBS)

.PHONY : clean 
clean : 
	-rm $(TARGET) $(OBJECTS)	
