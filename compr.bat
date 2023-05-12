gcc src/*.c src/glad/*.c ^
-static -Llib -lglfw3 -lgdi32 ^
-Iinclude ^
-O3 -s -mwindows ^
-o bin/release/hi.exe