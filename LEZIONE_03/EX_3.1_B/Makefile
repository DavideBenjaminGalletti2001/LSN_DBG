
main.exe : main.o random.o data_blocking.o derivati.o
	g++ random.o main.o data_blocking.o derivati.o -o main.exe
main.o : main.cpp random.h data_blocking.h
	g++ -c main.cpp -o main.o 
data_blocking.o: data_blocking.cpp data_blocking.h random.h
	g++ -c data_blocking.cpp -o data_blocking.o
derivati.o: derivati.cpp derivati.h random.cpp random.h
	g++ -c derivati.cpp -o derivati.o
random.o : random.cpp random.h
	g++ -c random.cpp -o random.o 
clean:
	rm *.o main.exe seed.out
