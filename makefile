# Forma estatica
S_FLAGS = -Wall -Llib -lraylib -lm -lpthread -ldl -lrt -lX11 
# Forma dinamica
D_FLAGS = -Wall -lraylib -lm -lpthread -ldl -lrt -lX11 

FLAGS = -Wall 
nomePrograma = moss
OBJS = 

all: $(nomePrograma)

$(nomePrograma): main.cpp
	g++ main.cpp -o $(nomePrograma) $(S_FLAGS)

run: $(nomePrograma)
	./$(nomePrograma)

clean:
	rm -f $(nomePrograma) $(OBJS)
