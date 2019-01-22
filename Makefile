compiler: main.o logger.o Makefile
	g++ -o build/j build/main.o build/logger.o -g

main.o: source/main.cpp source/Logger.h
	g++ -c source/main.cpp -o build/main.o -g

logger.o: source/Logger.cpp source/Logger.h
	g++ -c source/Logger.cpp -o build/logger.o -g

clean:
	rm -rf build
