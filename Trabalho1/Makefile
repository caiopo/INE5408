FLAGS=-Wall -Wextra -pedantic -std=c++11
# CPPS=Pista.cpp Carro.cpp Evento.cpp ListaOrdenada.cpp Semaforo.cpp Exceptions.cpp
CPPS={Pista,Carro,Evento,ListaOrdenada,Semaforo}.cpp
# CPPS=Semaforo.cpp

all:
	g++ ${FLAGS} ${CPPS} Main.cpp -o Main
	./Main
clean:
	rm Main