default:	build

build:	main.cpp
	g++ -g --stdlib=libc++ -Wall --std=c++11 -I/usr/local/Cellar/sdl2/2.0.12_1/include/SDL2/ -I/usr/local/Cellar/sdl2_image/2.0.5/include/SDL2/ -L/usr/local/lib -lSDL2 -lSDL2_image -o SDLTestCompiled.elf *.cpp ./Levels/Level1/*.cpp

run:	SDLTestCompiled.elf
	./SDLTestCompiled.elf

clean:
	rm *.elf
	rm -rf *.dSYM 