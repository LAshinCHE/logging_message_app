# Имя библиотеки
LIB_NAME = liblog_library

# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -fPIC
LDFLAGS = -shared

# Исходные файлы
SRC = log_library/log_library.cpp
HEADERS = log_library/log_library.h

# Целевой файл библиотеки
TARGET = $(LIB_NAME).so

# Правило по умолчанию
all: $(TARGET)

# Создание динамической библиотеки
$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(SRC)

# Очистка скомпилированных файлов
clean:
	rm -f $(TARGET)

# Установка (опционально)
install: $(TARGET)
	@echo "Установка $(TARGET) в /usr/local/lib"
	cp $(TARGET) /usr/local/lib
	@echo "Установка log_library.h в /usr/local/include"
	cp log_library.h /usr/local/include

# Деинсталляция (опционально)
uninstall:
	@echo "Удаление $(TARGET) из /usr/local/lib"
	rm -f /usr/local/lib/$(TARGET)
	@echo "Удаление log_library.h из /usr/local/include"
	rm -f /usr/local/include/log_library.h

.PHONY: all clean install uninstall
