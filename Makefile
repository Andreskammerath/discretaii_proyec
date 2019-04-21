CC = gcc
CCFLAGS = -g -Wextra -Wall -O3 -std=c99
TARGET = exe
SOURCES = Rii.c infoVerAri.c
OBJS = $(SOURCES:.c=.o)

all: $(TARGET)

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $^

$(TARGET): $(OBJS)
	$(CC) $(CCFLAGS) -o $(TARGET) $(OBJS)
	@echo "Make complete!!"

.PHONY: clean valgrind

clean:
	rm -f $(TARGET) $(OBJS)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-reachable=yes ./exe < test_grafos/300MIL.txt
	valgrind --leak-check=full --show-reachable=yes ./exe < test_grafos/bipartito/bipartito6.txt
	valgrind --leak-check=full --show-reachable=yes ./exe < test_grafos/bipartito/bipartito6mil
	valgrind --leak-check=full --show-reachable=yes ./exe < test_grafos/5millones.txt
	valgrind --leak-check=full --show-reachable=yes ./exe < test_grafos/bipartito/bipartitochoto.txt
	valgrind --leak-check=full --show-reachable=yes ./exe < test_grafos/queen13.txt
	valgrind --leak-check=full --show-reachable=yes ./exe < test_grafos/1500colores.txt
	valgrind --leak-check=full --show-reachable=yes ./exe < test_grafos/school1.txt

