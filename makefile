all: qSim

# Set CFLAGS to allow Debug and issue all warnings.
CFLAGS = -g -Wall

qSim: qSim.o
	g++ $(CFLAGS) qSim.o -o qSim

qSim.o: qSim.cpp qSim.h
	g++ $(CFLAGS) -c qSim.cpp

clean:
	rm -f qSim.o qSim
	rm -f -r html latex

docs:
	doxygen
	# Following lines are only needed if we want to access doc pages
	#   using a Web server.
	#chmod go+r html/*
	#cp html/* ~/public_html/cs2303assig3