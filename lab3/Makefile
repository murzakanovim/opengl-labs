# Имя компилируемого файла
TARGET = my_program

# Исходные файлы
SRCS = main.cpp

# Компилятор
CC = g++

# Флаги компиляции
CFLAGS = -std=c++11 -Wextra

# Директории с заголовочными файлами

# Директории с библиотеками

# Библиотеки
LIBS = -lglut -lGLU -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lSOIL

# Правило по умолчанию
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
