nomePrograma = moss
F_FLAGS = -Wall -Llib -lraylib -lm -lpthread -ldl -lrt -lX11 
FLAGS = -Wall 
OBJS = 

all: $(nomePrograma)

$(nomePrograma): main.cpp
	g++ main.cpp -o $(nomePrograma) $(F_FLAGS)

clean:
	rm -f $(nomePrograma) $(OBJS)
