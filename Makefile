CXX = g++
CXXOPTS = -Og -g -flto -std=gnu++17 -Wall -Wextra

HDRS = Globals.h Plane.h PlaneHistory.h Renderer.h Util.h
OBJS = Plane.o PlaneHistory.o Renderer.o Sim.o
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

sim: $(OBJS)
	$(CXX) $(CXXOPTS) -o $@ $^ $(LIBS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXOPTS) -c $<

.PHONY: run clean

run: sim
	./sim

clean:
	rm -f sim $(OBJS)
