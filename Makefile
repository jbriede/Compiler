# Make a build folder
$(shell mkdir -p build)

# Determine debugging


compiler: main.o logger.o parser.o lexer.o symboltable.o Makefile
	g++ -o build/j build/main.o build/logger.o build/parser.o build/lexer.o build/symboltable.o 

main.o: source/main.cpp source/Shared.h source/Parser.h source/Lexer.h source/SymbolTable.h source/Token.h
	g++ -c source/main.cpp -o build/main.o

parser.o: source/Parser.cpp source/Parser.h 
	g++ -c source/Parser.cpp -o build/parser.o

logger.o: source/Logger.cpp source/Logger.h
	g++ -c source/Logger.cpp -o build/logger.o

lexer.o: source/Lexer.cpp source/Lexer.h 
	g++ -c source/Lexer.cpp -o build/lexer.o

symboltable.o: source/SymbolTable.cpp source/SymbolTable.h 
	g++ -c source/SymbolTable.cpp -o build/symboltable.o


debug: main_d.o logger_d.o parser_d.o lexer_d.o symboltable_d.o  Makefile
	g++ -o build/j_d build/main_d.o build/logger_d.o build/parser_d.o build/lexer_d.o build/symboltable_d.o -g

main_d.o: source/main.cpp source/Shared.h source/Parser.h source/Lexer.h source/SymbolTable.h source/Token.h
	g++ -c source/main.cpp -o build/main_d.o -g

parser_d.o: source/Parser.cpp source/Parser.h source/Logger.h
	g++ -c source/Parser.cpp -o build/parser_d.o -g

logger_d.o: source/Logger.cpp source/Logger.h
	g++ -c source/Logger.cpp -o build/logger_d.o -g

lexer_d.o: source/Lexer.cpp source/Lexer.h 
	g++ -c source/Lexer.cpp -o build/lexer_d.o -g

symboltable_d.o: source/SymbolTable.cpp source/SymbolTable.h 
	g++ -c source/SymbolTable.cpp -o build/symboltable_d.o -g

clean:
	rm -rf build
