project: obj/main.o #obj/cat.o
	g++ -Wall obj/main.o -o project
	.\project.exe

obj/main.o: src/main.cpp
	g++ -Wall -c src/main.cpp -o obj/main.o

#obj/cat.o: src/cat.cpp src/include/cat.h
#	g++ -Wall -c src/cat.cpp -o obj/cat.o

build:
	g++ -Wall -c src/main.cpp -o obj/main.o
	g++ -Wall obj/main.o -o project

run: 
	.\project.exe

clean:
	del *.o project.exe