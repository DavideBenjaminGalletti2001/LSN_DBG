
main.exe : main.o random.o data_blocking.o metropolis.o
	g++ random.o main.o data_blocking.o  metropolis.o -o main.exe
main.o : main.cc random.h data_blocking.h
	g++ -c main.cc -o main.o 
data_blocking.o: data_blocking.cpp data_blocking.h random.h
	g++ -c data_blocking.cpp -o data_blocking.o
random.o : random.cpp random.h
	g++ -c random.cpp -o random.o 
metropolis.o: metropolis.cpp metropolis.h
	g++ -c metropolis.cpp -o metropolis.o
clean:
	rm *.o main.exe seed.out
clean_dat:
	rm *.dat
