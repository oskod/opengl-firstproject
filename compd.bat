gcc src/*.c src/glad/*.c ^
-static -Llib -lglfw3 -lgdi32 ^
-Iinclude ^
-DDEBUG ^
-o bin/release/hi.exe