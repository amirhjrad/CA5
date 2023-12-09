CC = g++
CFLAGS = -std=c++20 -Wall
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = bomberman
OUTPUT = bomberman.out

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(OUTPUT) $(SFML_LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)