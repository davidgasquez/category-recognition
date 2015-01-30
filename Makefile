#Makefile

all: folders clustering

clustering: src/clustering/clustering.cc src/clustering/main.cc
	g++ -o obj/clustering/main.o -c -Werror -g -Isrc src/clustering/main.cc
	g++ -o obj/clustering/clustering.o -c -Werror -g -Isrc src/clustering/clustering.cc
	g++ -o bin/clustering obj/clustering/main.o obj/clustering/clustering.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_nonfree -lopencv_features2d

folders:
	mkdir -p bin obj/clustering

clear:
	rm -r bin/* obj/*
