# Moss
My Own Super Server é um projeto de jogo no qual consiste em tratar os componentes
de uma máquina de servidor como se fossem estruturas de uma cidade. Assim, a terra seria a placa-mãe e as construções
os componentes que encaixam nela, como RAM, CPU, ... Os componentes são ligados por barramentos, ou melhor,
estradas, nas quais os cidadãos vão trafegar livremente carregando seus pacotes de dados.
A memória RAM e CPU precisam ser ligadas por barramentos para funcionar.

Alguns cidadãos são chamados de vírus, pois levam dados infectados (a ideia era montar uma mecânica em cima disso).

O projeto foi feito usando C++ e raylib.

# Compilação
## Linux
```
make -j4 
```

## Windows
```
mingw32-make.exe sys=win -j4
```

Apertando a tecla E você entra no modo de edição.
