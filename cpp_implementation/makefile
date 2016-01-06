flow : flow.o Graph.o Edge.o Node.o
	g++ -o flow flow.o Graph.o Edge.o Node.o

flow.o : flow.cpp Graph.hpp Edge.hpp Node.hpp
	g++ -c flow.cpp

Graph.o : Graph.cpp Graph.hpp Edge.hpp Node.hpp
	g++ -c Graph.cpp

Edge.o : Edge.cpp Edge.hpp Node.hpp enum.hpp
	g++ -c Edge.cpp

Node.o : Node.cpp Node.hpp Edge.hpp enum.hpp
	g++ -c Node.cpp
