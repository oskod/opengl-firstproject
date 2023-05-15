@echo off
set target=hello/triangle
if not [%1] == [] (set target=%1)
echo compiling %target%.c

gcc programs/%target%.c src/* ^
-static -Llib -lglfw3 -lgdi32 ^
-Iinclude ^
-O3 -s -mwindows ^
-o bin/release/comp