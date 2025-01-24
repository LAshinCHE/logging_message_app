# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC
LDFLAGS = -shared

# Названия файлов
TARGET = logger_app
LIBRARY = liblog_library.so
SOURCES = main.cpp
LIBRARY_SOURCES = record.cpp log_library.cpp
LIBRARY_OBJECTS = $(LIBRARY_SOURCES:.cpp=.o)
OBJECTS = $(SOURCES:.cpp=.o)

# Директории
BUILD_DIR = build
LIB_DIR = lib

# Правило по умолчанию
all: $(TARGET)

# Сборка динамической библиотеки
$(LIB_DIR)/$(LIBRARY): $(LIBRARY_OBJECTS)
	@mkdir -p $(LIB_DIR)
	$(CXX) $(LDFLAGS) -o $@ $(LIBRARY_OBJECTS)

# Сборка исполняемого файла
$(TARGET): $(OBJECTS) $(LIB_DIR)/$(LIBRARY)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) -L$(LIB_DIR) -llog_library

# Компиляция объектов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -rf $(TARGET) $(OBJECTS) $(LIBRARY_OBJECTS) $(LIB_DIR)

# Установка библиотеки
install: $(LIB_DIR)/$(LIBRARY)
	@sudo cp $(LIB_DIR)/$(LIBRARY) /usr/lib/
	@sudo ldconfig
	@echo "Library installed to /usr/lib/"

# Удаление библиотеки
uninstall:
	@sudo rm -f /usr/lib/$(LIBRARY)
	@sudo ldconfig
	@echo "Library removed from /usr/lib/"

.PHONY: all clean install uninstall
