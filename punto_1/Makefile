graph.pdf : graph.py sismo.dat
	python graph.py

sismo.dat : sismo.x
	./sismo.x > sismo.dat

sismo.x : sismo.c
	gcc sismo.c -o sismo.x -lm

clean :
	rm sismo.dat sismo.x graph.pdf
