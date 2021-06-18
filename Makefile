CXX = clang++
CFLAGS = -std=c++11 -O3
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -g

all: server client

server: server.o
	$(CXX) $(LDFLAGS) -o $(@) $(^)

client: client.o
	$(CXX) $(LDFLAGS) -o $(@) $(^)

.PHONY: test clean

test: server
	./server

clean:
	rm -f *.o server client

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $(@) $(<)