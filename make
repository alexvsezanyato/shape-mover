#!/bin/bash
SFMLPATH=SFML-2.5.1
IPATH=${SFMLPATH}/include
LPATH=${SFMLPATH}/lib
APPNAME=figure-mover
MAIN=main

g++ \
	-c src/${MAIN}.cpp \
	-o obj/${MAIN}.o \
	-I${IPATH}

g++ \
	-c src/App.cpp \
	-o obj/App.o \
	-I${IPATH}

g++ \
	-c src/Tshape.cpp \
	-o obj/Tshape.o \
	-I${IPATH}

g++ \
	-c src/WinApp.cpp \
	-o obj/WinApp.o \
	-I${IPATH}

g++ \
	-c src/TshapeMover.cpp \
	-o obj/TshapeMover.o \
	-I${IPATH}

g++ -no-pie \
	obj/${MAIN}.o obj/Tshape.o obj/App.o obj/WinApp.o obj/TshapeMover.o \
	-o bin/${APPNAME} \
	-L${LPATH} -lsfml-graphics -lsfml-window -lsfml-system

rm -f ${APPNAME}
ln bin/${APPNAME} ${APPNAME}
