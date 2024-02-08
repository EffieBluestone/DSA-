graph.exe: graph.cpp graph.h hash.cpp hash.h heap.cpp heap.h useDijkstra.cpp
	g++ --std=c++11 -o graph.exe graph.cpp hash.cpp heap.cpp useDijkstra.cpp 

debug.exe: graph.cpp graph.h hash.cpp hash.h heap.cpp heap.h useDijkstra.cpp
	g++ --std=c++11 -o debug.exe graph.cpp graph.h hash.cpp hash.h heap.cpp heap.h useDijkstra.cpp -ggdb
	
clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
