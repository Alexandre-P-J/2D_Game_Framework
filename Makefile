rebuild: clean
	make all

all: program

obj=main.o Object.o ObjectManager.o Player.o Map.o RenderScheduler.o Camera.o Event.o Engine.o Game.o
flags=-lSDL2 -lSDL2_image -g

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
RenderScheduler.o: RenderScheduler.cc
	g++ ${flags} -c RenderScheduler.cc -I .
Camera.o: Camera.cc
	g++ ${flags} -c Camera.cc -I .
Event.o: Event.cc
	g++ ${flags} -c Event.cc -I .
Engine.o: Engine.cc
	g++ ${flags} -c Engine.cc -I .
Game.o: Game.cc
		g++ ${flags} -c Game.cc -I .
clean:
	rm -f program
	rm -f *.o
	rm -f *.gch
