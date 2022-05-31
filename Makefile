all:main.o Game.o
	g++ -o main main.o Game.o
clean:
	$(RM) main *.o