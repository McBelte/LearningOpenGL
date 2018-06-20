IDIR = /includes


CXX=g++
CXXFLAGS= -I. -std=c++14
CXXLIBS = -lGL -lglfw -ldl
DEPS = 
OBJ = main.o glad.o Shader.o

%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(CXXLIBS)