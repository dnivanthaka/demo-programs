# Change the following values to suit your system.

CFLAGS=`sdl-config --cflags` -W -Wall -ggdb -O2
SDL_LIB=`sdl-config --libs` -lSDL_ttf -lSDL_image
CCC=g++

OBJECTS = manager.o sprite.o frame.o ioSingleton.o

run: main.o $(OBJECTS)
	$(CCC) $(CFLAGS) main.cpp -o run $(OBJECTS) $(SDL_LIB)

main.o: main.cpp manager.h
	$(CCC) $(CFLAGS) -c main.cpp

manager.o: manager.cpp manager.h background.h \
	ioSingleton.h
	$(CCC) $(CFLAGS) -c manager.cpp

sprite.o: sprite.cpp sprite.h frame.h ioSingleton.h
	$(CCC) $(CFLAGS) -c sprite.cpp

frame.o: frame.cpp frame.h ioSingleton.h
	$(CCC) $(CFLAGS) -c frame.cpp

ioSingleton.o: ioSingleton.cpp ioSingleton.h
	$(CCC) $(CFLAGS) -c ioSingleton.cpp

clean:
	rm -f run *.o
	rm -f *~
