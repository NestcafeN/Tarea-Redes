CXX = g++
CXXFLAGS = -std=c++11 -pthread -I$(COMMON_DIR)

# Directorios
SRC_DIR = src
BUILD_DIR = build
SERVER_DIR = $(SRC_DIR)/server
CLIENT_DIR = $(SRC_DIR)/client
COMMON_DIR = $(SRC_DIR)/common

# Archivos de objeto
SERVER_OBJ = $(BUILD_DIR)/server.o $(BUILD_DIR)/common.o
CLIENT_OBJ = $(BUILD_DIR)/client.o $(BUILD_DIR)/common.o

all: $(BUILD_DIR)/server $(BUILD_DIR)/client

# Reglas para compilar el servidor
$(BUILD_DIR)/server: $(SERVER_OBJ)
        $(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/server $(SERVER_OBJ)

# Reglas para compilar el cliente
$(BUILD_DIR)/client: $(CLIENT_OBJ)
        $(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/client $(CLIENT_OBJ)

# Reglas para compilar los archivos de objeto del servidor
$(BUILD_DIR)/server.o: $(SERVER_DIR)/server.cpp $(COMMON_DIR)/common.hpp
        $(CXX) $(CXXFLAGS) -c $(SERVER_DIR)/server.cpp -o $(BUILD_DIR)/server.o

# Reglas para compilar los archivos de objeto del cliente
$(BUILD_DIR)/client.o: $(CLIENT_DIR)/client.cpp $(COMMON_DIR)/common.hpp
        $(CXX) $(CXXFLAGS) -c $(CLIENT_DIR)/client.cpp -o $(BUILD_DIR)/client.o

# Reglas para compilar los archivos de objeto comunes
$(BUILD_DIR)/common.o: $(COMMON_DIR)/common.cpp $(COMMON_DIR)/common.hpp
        $(CXX) $(CXXFLAGS) -c $(COMMON_DIR)/common.cpp -o $(BUILD_DIR)/common.o

# Regla para limpiar los archivos de objeto y ejecutables
clean:
        rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/server $(BUILD_DIR)/client