#
# AC - 2019/2020 MIEI FCT/UNL
# 2018-2020 vad
# 

CFLAGS += -g -std=c11 -Wall -pthread
CC = cc

SRC = main.c driver.c hw.c
TARGET = main


$(TARGET):	$(SRC:%.c=%.o)
	$(CC) -o $@  $^ -pthread

teste:	teste.o driver.o hw.o
	$(CC) -o $@  $^ -pthread

all: $(TARGET) teste

clean:
	rm -f $(TARGET) teste teste.o $(SRC:%.c=%.o) $(SRC:%.c=%.d) *~ *.bak Makefile.deps


#deps:
#	makedepend -Y -f Makefile.deps -- $(CFLAGS) -- $(SRC)

driver.o: hw.h driver.h
hw.o: hw.h
main.o: hw.h

