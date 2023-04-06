all: pa14.cpp Container.hpp
	$(CXX) $(CXXFLAGS) pa14.cpp -o pa14

test: Container-test.cpp Container.hpp
	$(CXX) $(CXXFLAGS) Container-test.cpp -o Container-test

clean:
	rm -f pa14 Container-test

turnin:
	turnin -c cs202 -p pa14 -v \
		pa14.cpp Container.hpp Container-test.cpp Makefile

