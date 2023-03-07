PROGRAM = crunch
CC = gcc
CFLAGS = -g3
#gcc -g3 -o crunch crunch.c
${PROGRAM}:	${PROGRAM}.c
		${CC}  ${CFLAGS} -o ${PROGRAM} ${PROGRAM}.c

clean:
		rm -f ${PROGRAM}
