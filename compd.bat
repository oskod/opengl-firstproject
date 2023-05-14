@echo off
set target=hello/triangle
if not [%1] == [] (set target=%1)
echo compiling %target%.c

gcc programs/%target%.c src/*.c ^
-static -Llib -lglfw3 -lgdi32 ^
-Iinclude ^
-DDEBUG ^
-o bin/debug/comp