
.PHONY: check-syntax

all:
	gcc -Wall -ansi -pedantic -mindirect-branch=thunk -o facerec facerec.c -ldeep -lm -fopenmp

check-syntax:
	gcc -Wall -ansi -pedantic -mindirect-branch=thunk -o facerec facerec.c -ldeep -lm -fopenmp -fsyntax-only

debug:
	gcc -Wall -ansi -pedantic -mindirect-branch=thunk -g -o facerec facerec.c -ldeep -lm -fopenmp

clean:
	rm -f *.o facerec *.png *.plist
