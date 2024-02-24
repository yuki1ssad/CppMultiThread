.PHONY: run clean
ALL = main

run:
	@g++ $(ALL).cpp -o $(ALL).o -std=c++11 -lpthread
	@./$(ALL).o
	@make clean

clean:
	@rm *.o