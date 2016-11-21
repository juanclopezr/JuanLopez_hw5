graph.pdf : graph.py sun.dat
	python graph.py

sun.dat : sun.x
	./sun.x > sun.dat

sun.x : sun.c
	gcc sun.c -o sun.x -lm

clean :
	rm sun.x graph.pdf
