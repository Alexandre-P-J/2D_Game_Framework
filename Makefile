all: program

obj=main.o Object.o ObjectManager.o Player.o Map.o
flags=-lSDL2 -lSDL2_image

program: ${obj}
	g++ ${flags} ${obj} -o program
main.o: main.cc
	g++ ${flags} -c main.cc -I .
Object.o: Object.cc
	g++ ${flags} -c Object.cc -I .
ObjectManager.o: ObjectManager.cc
	g++ ${flags} -c ObjectManager.cc -I .
Player.o: Player.cc
	g++ ${flags} -c Player.cc -I .
Map.o: Map.cc
	g++ ${flags} -c Map.cc -I .
rb: clean all

clean:
	rm -f program
	rm -f *.o
