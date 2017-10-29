all:main
	./main
main:main.cpp myqueue.cpp
	g++ -o main main.cpp myqueue.cpp -std=c++11 -g -lm
