all:
	g++ main.cpp -pthread -o main
	
clean:
	$(RM) run