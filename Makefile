rebuild: clean
	make all

all: program

obj=main.o Object.o Player.o Map.o RenderScheduler.o Camera.o Engine.o Game.o Input.o Animation.o
flags=-lSDL2 -lSDL2_image -lBox2D -g

program: ${obj}
	g++ ${flags} ${obj} -o program
main.o: main.cc
	g++ ${flags} -c main.cc -I .
Object.o: Object.cc
	g++ ${flags} -c Object.cc -I .
Player.o: Player.cc
	g++ ${flags} -c Player.cc -I .
Map.o: Map.cc
	g++ ${flags} -c Map.cc -I .
RenderScheduler.o: RenderScheduler.cc
	g++ ${flags} -c RenderScheduler.cc -I .
Camera.o: Camera.cc
	g++ ${flags} -c Camera.cc -I .
Engine.o: Engine.cc
	g++ ${flags} -c Engine.cc -I .
Game.o: Game.cc
	g++ ${flags} -c Game.cc -I .
Input.o: Input.cc
	g++ ${flags} -c Input.cc -I .
Animation.o: Animation.cc
	g++ ${flags} -c Animation.cc -I .
clean:
	rm -f program
	rm -f *.o
	rm -f *.gch
