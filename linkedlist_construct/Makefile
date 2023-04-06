pa17a: pa17a.o simple_list.o
	$(CXX) $(CXXFLAGS) pa17a.o simple_list.o -o pa17a

pa17a.o: pa17a.cpp simple_list.h
	$(CXX) $(CXXFLAGS) pa17a.cpp -c

simple_list_test: simple_list_test.o simple_list.o
	$(CXX) $(CXXFLAGS) simple_list_test.o simple_list.o -o test

simple_list_test.o: simple_list_test.cpp simple_list.h
	$(CXX) $(CXXFLAGS) simple_list_test.cpp -c

simple_list.o: simple_list.cpp simple_list.h
	$(CXX) $(CXXFLAGS) simple_list.cpp -c

clean:
	rm  -f pa17a pa17a.o simple_list.o simple_list_test.o

turnin:
	turnin -c cs202 -p pa17a -v \
		simple_list.h simple_list.cpp pa17a.cpp simple_list_test.cpp Makefile