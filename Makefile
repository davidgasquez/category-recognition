#Makefile

all: folders
	g++ -o obj/bow.o -c -Werror -O2 -Isrc src/bow.cc
	g++ -o bin/bow obj/bow.o -lopencv_core -lopencv_highgui -lopencv_nonfree -lopencv_features2d -lopencv_ml
	g++ -o obj/classify.o -c -Werror -O2 -Isrc src/classify.cc
	g++ -o bin/classify obj/classify.o -lopencv_core -lopencv_highgui -lopencv_nonfree -lopencv_features2d -lopencv_ml
	g++ -o obj/clustering.o -c -Werror -O2 -Isrc src/clustering.cc
	g++ -o bin/make_vocabulary obj/clustering.o -lopencv_core -lopencv_highgui -lopencv_nonfree -lopencv_features2d
	g++ -o obj/testing.o -c -Werror -O2 -Isrc src/testing.cc
	g++ -o bin/test obj/testing.o -lopencv_core -lopencv_highgui -lopencv_nonfree -lopencv_features2d -lopencv_ml

folders:
	mkdir -p bin obj/clustering

clear:
	rm -r bin/* obj/*
