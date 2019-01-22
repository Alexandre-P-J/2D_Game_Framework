rebuild: clean
	make all

all: game.x

obj=main.o Object.o Player.o Map.o RenderComponent.o Camera.o Engine.o Game.o InputComponent.o Animation.o
flags=-lSDL2 -lSDL2_image -lBox2D -g

game.x: ${obj}
	g++ ${flags} ${obj} -o game.x
main.o: main.cc
	g++ ${flags} -c main.cc -I .
Object.o: Object.cc
	g++ ${flags} -c Object.cc -I .
Player.o: Player.cc
	g++ ${flags} -c Player.cc -I .
Map.o: Map.cc
	g++ ${flags} -c Map.cc -I .
RenderComponent.o: RenderComponent.cc
	g++ ${flags} -c RenderComponent.cc -I .
Camera.o: Camera.cc
	g++ ${flags} -c Camera.cc -I .
Engine.o: Engine.cc
	g++ ${flags} -c Engine.cc -I .
Game.o: Game.cc
	g++ ${flags} -c Game.cc -I .
InputComponent.o: InputComponent.cc
	g++ ${flags} -c InputComponent.cc -I .
Animation.o: Animation.cc
	g++ ${flags} -c Animation.cc -I .
clean:
	rm -f *.x
	rm -f *.o
	rm -f *.gch
