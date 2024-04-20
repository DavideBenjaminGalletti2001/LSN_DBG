
main.exe : main.o random.o data_blocking.o random_walk.o
	g++ random.o main.o data_blocking.o random_walk.o -o main.exe
main.o : main.cpp random.h data_blocking.h
	g++ -c main.cpp -o main.o 
random.o : random.cpp random.h
	g++ -c random.cpp -o random.o 
data_blocking.o: data_blocking.cpp data_blocking.h random.h
	g++ -c data_blocking.cpp -o data_blocking.o
random_walk.o: random_walk.cpp random_walk.h data_blocking.h random.h
	g++ -c random_walk.cpp -o random_walk.o
clean:
	rm *.o main.exe seed.out
