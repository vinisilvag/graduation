CC=g++
CFLAGS=-std=c++14 -Wall
TARGET=vpl_execution

BUILD   	:= build
SRC     	:= src
ENTITIES    := entidades
INCLUDE 	:= include

${BUILD}/${TARGET}: ${BUILD}/Pessoa.o ${BUILD}/Funcionario.o ${BUILD}/Professor.o ${BUILD}/main.o
	${CC} ${CFLAGS} -o ./${TARGET} ${BUILD}/*.o

${BUILD}/Pessoa.o: ${INCLUDE}/Pessoa.hpp ${SRC}/${ENTITIES}/Pessoa.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/${ENTITIES}/Pessoa.cpp -o ${BUILD}/Pessoa.o

${BUILD}/Funcionario.o: ${INCLUDE}/Funcionario.hpp ${SRC}/${ENTITIES}/Funcionario.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/${ENTITIES}/Funcionario.cpp -o ${BUILD}/Funcionario.o

${BUILD}/Professor.o: ${INCLUDE}/Professor.hpp ${SRC}/${ENTITIES}/Professor.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/${ENTITIES}/Professor.cpp -o ${BUILD}/Professor.o

${BUILD}/main.o: ${INCLUDE}/Pessoa.hpp ${INCLUDE}/Funcionario.hpp ${INCLUDE}/Professor.hpp ${SRC}/main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/main.cpp -o ${BUILD}/main.o

clean:
	rm -f ${BUILD}/*
