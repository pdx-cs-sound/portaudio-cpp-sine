CPP = g++ -g
CPPFLAGS = -Wall -Wextra -I/usr/include/portaudio
LIBS = -lportaudio -lpthread -lm -ldl

sine: sine.o
	$(CPP) $(CPPFLAGS) -o $@ $^ $(LIBS)

clean:
	-rm -f *.o sine
