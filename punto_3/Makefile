graph.pdf : graph.py diff.dat
	python graph.py

diff.dat : diff.x
	./diff.x > diff.dat

diff.x : diff.c
	gcc diff.c -o diff.x -lm

clean :
	rm graph.pdf diff.x diff.dat
