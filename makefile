# Forma dinamica linux
D_FLAGS = -Wall -lraylib -lm -lpthread -ldl -lrt -lX11 
nomePrograma = moss
OBJS = src/Effect.o src/Camera.o src/Map.o main.o

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

Camera.o: src/Camera.cpp src/Camera.hpp
	g++ -c src/Camera.cpp $(FLAGS)

Map.o: src/Map.cpp src/Map.hpp
	g++ -c src/Map.cpp $(FLAGS)

Effect.o: src/Effect.cpp src/Effect.hpp
	g++ -c src/Effect.cpp $(FLAGS)

run: $(nomePrograma)
	./$(nomePrograma)

clean:
	rm -f $(nomePrograma) $(OBJS)
