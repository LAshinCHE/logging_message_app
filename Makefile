# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC
LDFLAGS = -shared

# Названия файлов
TARGET = logger_app
LIBRARY = liblog_library.so
SOURCES = main.cpp
LIBRARY_SOURCES = log_library/record.cpp log_library/log_library.cpp
LIBRARY_OBJECTS = $(LIBRARY_SOURCES:.cpp=.o)
OBJECTS = $(SOURCES:.cpp=.o)

# Директории
BUILD_DIR = build
LIB_DIR = log_library

# Правило по умолчанию
all: $(TARGET)

# Сборка динамической библиотеки
$(LIB_DIR)/$(LIBRARY): $(LIBRARY_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(LIBRARY_OBJECTS)

# Сборка исполняемого файла
$(TARGET): $(OBJECTS) $(LIB_DIR)/$(LIBRARY)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) -L$(LIB_DIR) -llog_library

# Компиляция объектов библиотеки
log_library/%.o: log_library/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Компиляция объектов основной программы
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Запуск программы с заданным LD_LIBRARY_PATH
run: $(TARGET)
	LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH ./$(TARGET) logfile.txt 1

# Очистка
clean:
	rm -rf $(TARGET) $(OBJECTS) $(LIBRARY_OBJECTS) $(LIB_DIR)/$(LIBRARY)

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

.PHONY: all clean install uninstall run
