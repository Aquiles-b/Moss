# Forma dinamica linux
D_FLAGS = -Wall -lraylib -lm -lpthread -ldl -lrt -lX11 
nomePrograma = moss
OBJS = src/Camera.o src/Mapa.o

all: $(nomePrograma)

sys = linux
ifeq ($(sys), win)
	#Estatica Windows
	S_FLAGS = -Wall -Iinclude -LlibWin -static -static-libgcc -static-libstdc++ -lraylib -lopengl32 -lgdi32 -lwinmm
else
	#Estatica Linux
	S_FLAGS = -Wall -Llib -lraylib -lm -lpthread -ldl -lrt -lX11 
endif
FLAGS = -Wall 

$(nomePrograma): main.cpp $(OBJS)
	g++ main.cpp -o $(nomePrograma) $(OBJS) $(S_FLAGS)

Camera.o: src/Camera.cpp src/Camera.hpp
	g++ -c src/Camera.cpp $(FLAGS)

Mapa.o: src/Mapa.cpp src/Mapa.hpp
	g++ -c src/Mapa.cpp $(FLAGS)

run: $(nomePrograma)
	./$(nomePrograma)

clean:
	rm -f $(nomePrograma) $(OBJS)
