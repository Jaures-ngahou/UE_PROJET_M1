CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = manager
SRCS = main.c cgroup_limit.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET) mount

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o: main.c cgroup_limit.h
	$(CC) $(CFLAGS) -c main.c

cgroup_limit.o: cgroup_limit.c cgroup_limit.h
	$(CC) $(CFLAGS) -c cgroup_limit.c

clean:
	rm -f $(OBJS) $(TARGET)

mount:
	sudo mount -o remount,rw /sys/fs/cgroup/
	sudo cgcreate -g cpu,memory:tst

