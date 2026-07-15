###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author: Charles Man

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

CalcYouLater: RPNCalc.o DatumStack.o Datum.o main.o
	$(CXX) $(LDFLAGS) -o $@ $^

main.o: main.cpp RPNCalc.h DatumStack.h Datum.h
	${CXX} ${CXXFLAGS} -c main.cpp

RPNCalc.o: RPNCalc.cpp RPNCalc.h DatumStack.h Datum.h
	${CXX} ${CXXFLAGS} -c RPNCalc.cpp

DatumStack.o: DatumStack.cpp DatumStack.h Datum.h
	${CXX} ${CXXFLAGS} -c DatumStack.cpp

unit_test: unit_test_driver.o DatumStack.o Datum.o
	${CXX} ${CXXFLAGS} $^

clean:
	rm DatumStack.o a.out

provide:
	provide comp15 proj2_calcyoulater DatumStack.h DatumStack.cpp \
					unit_tests.h RPNCalc.h \
					RPNCalc.cpp main.cpp README Makefile add.cyl \
					fact.cyl fib.cyl fib_debug.cyl \

Datum+vector_example.o: Datum+vector_example.cpp Datum.h

Datum+vector_example: Datum+vector_example.o Datum.o
	${CXX} ${LDFLAGS} -o $@ $^

%.cylc:  %.cyl
	./cylc $^
