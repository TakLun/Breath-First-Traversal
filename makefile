all: submission

submission: minSemesters.o
	g++ -g minSemesters.o -o submission
	
minSemesters.o: minSemesters.cpp
	g++ -g -c minSemesters.cpp
	
clean:
	rm -f *.o submission
