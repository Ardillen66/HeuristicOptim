
program : src/pfspinstance.h \ 
	src/experiments.h src/initialsolution.h src/initialsolutionRand.h src/initialsolutionRZ.h src/neighbourhoods.h src/neighbourhoodsExchange.h src/neighbourhoodsInsert.h \
	src/neighbourhoodsTranspose.h src/pivoting.h src/pivotingBest.h src/pivotingFirst.h \
	src/flowshop.cpp src/pfspinstance.cpp src/experiments.cpp src/initialsolution.cpp src/initialsolutionRand.cpp src/initialsolutionRZ.cpp src/neighbourhoods.cpp src/neighbourhoodsExchange.cpp \
	src/neighbourhoodsInsert.cpp src/neighbourhoodsTranspose.cpp src/pivoting.cpp src/pivotingBest.cpp src/pivotingFirst.cpp src/test.cpp

	g++ -O3 -std=c++0x -c ./src/helpers.cpp -o src/helpers.o
	g++ -O3 -std=c++0x -c ./src/flowshop.cpp -o src/flowshop.o
	g++ -O3 -std=c++0x -c ./src/pfspinstance.cpp -o src/pfspinstance.o
	g++ -O3 -std=c++0x -c ./src/experiments.cpp -o src/experiments.o
	g++ -O3 -std=c++0x -c ./src/initialsolution.cpp -o src/initialsolution.o
	g++ -O3 -std=c++0x -c ./src/initialsolutionRand.cpp -o src/initialsolutionRand.o
	g++ -O3 -std=c++0x -c ./src/initialsolutionRZ.cpp -o src/initialsolutionRZ.o
	g++ -O3 -std=c++0x -c ./src/neighbourhoods.cpp -o src/neighbourhoods.o
	g++ -O3 -std=c++0x -c ./src/neighbourhoodsExchange.cpp -o src/neighbourhoodsExchange.o
	g++ -O3 -std=c++0x -c ./src/neighbourhoodsInsert.cpp -o src/neighbourhoodsInsert.o
	g++ -O3 -std=c++0x -c ./src/neighbourhoodsTranspose.cpp -o src/neighbourhoodsTranspose.o
	g++ -O3 -std=c++0x -c ./src/pivoting.cpp -o src/pivoting.o
	g++ -O3 -std=c++0x -c ./src/pivotingBest.cpp -o src/pivotingBest.o
	g++ -O3 -std=c++0x -c ./src/pivotingFirst.cpp -o src/pivotingFirst.o
	g++ -O3 -std=c++0x -c ./src/test.cpp -o src/test.o

	g++ -O3  src/pivoting.o src/pivotingBest.o src/pivotingFirst.o src/neighbourhoods.o src/neighbourhoodsTranspose.o src/neighbourhoodsInsert.o \
			src/neighbourhoodsExchange.o src/initialsolution.o src/initialsolutionRand.o src/initialsolutionRZ.o \
			src/experiments.o src/flowshop.o src/pfspinstance.o src/test.o -o flowshopWCT

clean:
	rm src/*.o flowshopCWT

g++ -O3  src/helpers.o src/pivoting.o src/pivotingBest.o src/pivotingFirst.o src/neighbourhoods.o src/neighbourhoodsTranspose.o src/neighbourhoodsInsert.o src/neighbourhoodsExchange.o src/initialsolution.o src/initialsolutionRand.o src/initialsolutionRZ.o src/experiments.o src/flowshop.o src/pfspinstance.o src/test.o -o flowshopWCT