CC = clang++
FLAGS = -Wall -pedantic
INC = -I common/include
SYS_LIB = -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi
STATIC = common/linux_x86_64/libGLEW.a common/linux_x86_64/libglfw3.a

all: examplebuild

examplebuild:
	${CC} ${FLAGS} -o example64 example.cpp text.cpp ${STATIC} ${INC} ${SYS_LIB}
