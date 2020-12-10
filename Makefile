CC = gcc

all: binarysearchtree efunc fileparse guessnumber integrate ip measurement palindrom pong primfac pythagoras singlylinkedlist weekday

binarysearchtree:
	$(CC) binarysearchtree.c -o binarysearchtree
efunc:
	$(CC) efunc.c -o efunc -lm
fileparse:
	$(CC) fileparse.c -o fileparse
guessnumber:
	$(CC) guessnumber.c -o guessnumber
integrate:
	$(CC) integrate.c -o integrate -lm
ip:
	$(CC) ip.c -o ip
measurement:
	$(CC) measurement.c -o measurement
palindrom:
	$(CC) palindrom.c -o palindrom
pong:
	$(CC) pong.c -o pong -lcurses
primfac:
	$(CC) primfac.c -o primfac
pythagoras:
	$(CC) pythagoras.c -o pythagoras
singlylinkedlist:
	$(CC) singlylinkedlist.c -o singlylinkedlist
weekday:
	$(CC) weekday.c -o weekday
