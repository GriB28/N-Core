@echo off

set "SFML=path/to/SFML/"

mkdir ".build"

echo compiling...
g++ -O2 -DDEBUG_ -DSFML_STATIC -ggdb3 -std=c++17 ^
    -I"%SFML%include" -L"%SFML%lib" ^
    *.cpp source/*.cpp scenes/*.cpp utils/*.cpp player/*.cpp level/*.cpp ^
    -lsfml-audio-s -lsfml-network-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s ^
    -lopengl32 -lfreetype -lwinmm -lgdi32 -lopenal32 -lflac ^
    -lvorbisfile -lvorbisenc -lvorbis -logg ^
    -static -static-libgcc -static-libstdc++ ^
    -o ".build/N-Core.exe"
echo finished!

echo starting...
cd ".build"
N-Core.exe
cd ..
