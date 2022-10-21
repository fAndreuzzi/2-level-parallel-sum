.DEFAULT_GOAL := compile

SRC = src/data.cpp src/utils.cpp src/algebra-simulation.cpp
OUT = algebra-simulation

memory:
	mpic++ -fsanitize=address $(SRC) -o $(OUT)

compile:
	mpic++ -O3 -march=native $(SRC) -o $(OUT)

clean:
	rm *.x
	rm *.gch
