all: matioCPP_test

HPP_FILES:= *.hpp
LD_FLAGS += `pkg-config --libs --cflags matio`
CC_FLAGS := -O3 -std=c++14 -Wall -Wextra -pedantic -march=native

%.o: %.cpp $(HPP_FILES)
	$(CXX) $(CC_FLAGS) $(IFLAGS) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

matioCPP_test : main.o
	$(CXX) -o $@ $^ $(LD_FLAGS) $(CPPFLAGS) $(CFLAGS)

clean:
	rm -f matioCPP_test && rm -f *.o

run: matioCPP_test
	./matioCPP_test
