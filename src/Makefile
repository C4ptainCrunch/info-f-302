CXXFLAGS = -ggdb  -std=c++11 -O4
TARGET = solver
LDFLAGS = -lm

${TARGET}: Solver.o main.o
	${CXX} -o $@ $^ ${LDFLAGS}

.PHONY: clean mrproper

clean:
	rm -f *.o

mrproper: clean
	rm -f ${TARGET}
