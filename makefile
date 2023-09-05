# Forma dinamica linux
D_FLAGS = -Wall -lraylib -lm -lpthread -ldl -lrt -lX11 
nomePrograma = moss
OBJS = src/RobotsController.o src/GameController.o src/Robot.o src/Hud.o src/Construction.o src/ComponentModel.o src/Animation.o src/Camera.o src/Map.o main.o

all: $(nomePrograma)

sys = linux
ifeq ($(sys), win)
	#Estatica Windows
	S_FLAGS = -Wall -Iinclude -LlibWin -static -static-libgcc -static-libstdc++ -lraylib -lopengl32 -lgdi32 -lwinmm
else
	#Estatica Linux
	S_FLAGS = -Wall -Llib -lraylib -lm -lpthread -ldl -lrt -lX11 
endif
FLAGS = -Wall -O3

$(nomePrograma): $(OBJS) 
	g++ -o $(nomePrograma) $(OBJS) $(S_FLAGS)

main.o: main.cpp
	g++ -c main.cpp $(FLAGS) 

Camera.o: src/Camera.cpp headers/Camera.hpp
	g++ -c src/Camera.cpp $(FLAGS)

Map.o: src/Map.cpp headers/Map.hpp
	g++ -c src/Map.cpp $(FLAGS)

Animation.o: src/Animation.cpp headers/Animation.hpp
	g++ -c src/Animation.cpp $(FLAGS)

ComponentModel.o: src/ComponentModel.cpp headers/ComponentModel.hpp
	g++ -c src/ComponentModel.cpp $(FLAGS)

Construction.o: src/Construction.cpp headers/Construction.hpp
	g++ -c src/Construction.cpp $(FLAGS)

Hud.o: src/Hud.cpp headers/Hud.hpp
	g++ -c src/Hud.cpp $(FLAGS)

Robot.o: src/Robot.cpp headers/Robot.hpp
	g++ -c src/Robot.cpp $(FLAGS)

GameController.o: src/GameController.cpp headers/GameController.hpp
	g++ -c src/GameController.cpp $(FLAGS)

RobotsController.o: src/RobotsController.cpp headers/RobotsController.hpp headers/Construction.hpp
	g++ -c src/RobotsController.cpp $(FLAGS)

run: $(nomePrograma)
	./$(nomePrograma)

clean:
	rm -f $(nomePrograma) $(OBJS)
