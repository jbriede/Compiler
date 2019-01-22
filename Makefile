# Make a build folder
$(shell mkdir -p build)

# Determine debugging


compiler: main.o logger.o parser.o Makefile
	g++ -o build/j build/main.o build/logger.o build/parser.o 

main.o: source/main.cpp source/Logger.h
	g++ -c source/main.cpp -o build/main.o

parser.o: source/Parser.cpp source/Parser.h source/Logger.h
	g++ -c source/Parser.cpp -o build/parser.o

logger.o: source/Logger.cpp source/Logger.h
	g++ -c source/Logger.cpp -o build/logger.o


debug: main_d.o logger_d.o parser_d.o Makefile
	g++ -o build/j_d build/main_d.o build/logger_d.o build/parser_d.o -g

main_d.o: source/main.cpp source/Logger.h
	g++ -c source/main.cpp -o build/main_d.o -g

parser_d.o: source/Parser.cpp source/Parser.h source/Logger.h
	g++ -c source/Parser.cpp -o build/parser_d.o -g

logger_d.o: source/Logger.cpp source/Logger.h
	g++ -c source/Logger.cpp -o build/logger_d.o -g

clean:
	rm -rf build
