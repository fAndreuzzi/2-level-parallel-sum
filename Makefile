.DEFAULT_GOAL := compile

memory:
	mpic++ -fsanitize=address src/algebra-simulation.cpp -o algebra-simulation

compile:
	mpic++ -O3 -march=native src/algebra-simulation.cpp -o algebra-simulation

clean:
	rm *.x
	rm *.gch
