# Forma estatica
S_FLAGS = -Wall -Llib -lraylib -lm -lpthread -ldl -lrt -lX11 
# Forma dinamica
D_FLAGS = -Wall -lraylib -lm -lpthread -ldl -lrt -lX11 

FLAGS = -Wall 
nomePrograma = moss
OBJS = src/Camera.o src/Mapa.o

all: $(nomePrograma)

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
