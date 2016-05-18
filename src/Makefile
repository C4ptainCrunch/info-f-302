CXXFLAGS = -ggdb
TARGET = solver
LDFLAGS = -lm

${TARGET}: Solver.o main.o
	${CXX} -o $@ $^ ${LDFLAGS}

.PHONY: clean mrproper

clean:
	rm -f *.o

mrproper: clean
	rm -f ${TARGET}
