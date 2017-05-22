#############
#Compilation#
#############

Makefile is broken, compile an link by hand instead.

Compile commands:
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
g++ -O3 -std=c++0x -c ./src/iga.cpp -o src/iga.o
g++ -O3 -std=c++0x -c ./src/aco.cpp -o src/aco.o

Link command:
g++ -O3  src/aco.o src/iga.o src/helpers.o src/pivoting.o src/pivotingBest.o src/pivotingFirst.o src/neighbourhoods.o src/neighbourhoodsTranspose.o src/neighbourhoodsInsert.o src/neighbourhoodsExchange.o src/initialsolution.o src/initialsolutionRand.o src/initialsolutionRZ.o src/experiments.o src/flowshop.o src/pfspinstance.o src/test.o -o flowshopWCT

#######
#Usage#
#######

To run a full experiment on all instances and print result to terminal.

On terminal in this folder:

flowshopWCT ii --<pivot_rule> --<neighbourhood> --<initialization>
[
<pivot_rule> = best/first
<neighbourhood> = insert/transpose/exchange
<initialization> = random/rz
]

OR

flowshopWCT vnd --<neighbourhood_order> --<initialization>
[
<neighbourhood_order> = t_e_i/t_i_e
]

OR

flowshopWCT sls --<initial_ls_pivot_rule> --<neighbourhood> --<aco_trail_persistence> --<iga_d> --<iga_lambda> --<deviation>
 


