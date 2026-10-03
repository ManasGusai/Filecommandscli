CFLAGS = -Wall -Wextra
TARGET = fs

debug:
	g++ $(CFLAGS) -DDEBUG main.cpp commands.cpp token.cpp debug.cpp lexer.cpp parser.cpp executor.cpp -o $(TARGET)

release:
	g++ $(CFLAGS) main.cpp commands.cpp token.cpp debug.cpp lexer.cpp parser.cpp executor.cpp -o $(TARGET)
