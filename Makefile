CXX = g++
CXXFLAGS = -std=c++11 -pthread

all: servidor cliente

servidor: servidor.o common.o
        $(CXX) $(CXXFLAGS) -o servidor servidor.o common.o

cliente: cliente.o common.o
        $(CXX) $(CXXFLAGS) -o cliente cliente.o common.o

servidor.o: servidor.cpp common.hpp
        $(CXX) $(CXXFLAGS) -c servidor.cpp

cliente.o: cliente.cpp common.hpp
        $(CXX) $(CXXFLAGS) -c cliente.cpp

common.o: common.cpp common.hpp
        $(CXX) $(CXXFLAGS) -c common.cpp

clean:
        rm -f *.o servidor cliente