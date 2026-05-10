CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lm
TARGET = main

# Lista de archivos fuente
SRCS = main.c archivotxt.c bfs.c city_model.c graph.c
# Genera la lista de archivos objeto (.o) a partir de los .c
OBJS = $(SRCS:.c=.o)

# Regla principal: compila el ejecutable
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Regla para compilar archivos .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJS) $(TARGET)

# Regla para compilar y ejecutar de una vez
run: all
	./$(TARGET)
