CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -I.
LIBS = -lcurl
PRODUCT_NAME = kurkur

DEBUG_DIR = build/debug
DEBUG_FLAGS = -g -O0
DEBUG_TARGET = $(DEBUG_DIR)/$(PRODUCT_NAME)

RELEASE_DIR = build/release
RELEASE_FLAGS = -O3 -DNDEBUG
RELEASE_TARGET = $(RELEASE_DIR)/$(PRODUCT_NAME)

SOURCES = main.cpp \
          src/app/Application.cpp \
          src/app/ExchangeRateProvider.cpp \
          src/app/NotificationService.cpp \
          src/utils/TimeUtils.cpp \
          third_party/pugixml.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: debug release

debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(SOURCES)
	@mkdir -p $(DEBUG_DIR)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(SOURCES) -o $(DEBUG_TARGET) $(LIBS)
	@echo "Debug build ready: $(DEBUG_TARGET)"

release: $(RELEASE_TARGET)

$(RELEASE_TARGET): $(SOURCES)
	@mkdir -p $(RELEASE_DIR)
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) $(SOURCES) -o $(RELEASE_TARGET) $(LIBS)
	@echo "Release build ready: $(RELEASE_TARGET)"

clean:
	rm -rf build
	rm -f *.o $(PRODUCT_NAME)
	@echo "Cleaning completed"

install: release
	cp $(RELEASE_TARGET) /usr/local/bin/$(PRODUCT_NAME)
	@echo "Application installed: /usr/local/bin/$(PRODUCT_NAME)"

help:
	@echo "Available targets:"
	@echo "  all          - Builds both Debug and Release versions (default)"
	@echo "  debug        - Builds Debug version"
	@echo "  release      - Builds Release version"
	@echo "  clean        - Cleans build directories and compilation products"
	@echo "  install      - Installs Release application to /usr/local/bin"
	@echo "  run          - Runs Debug version (same as run-debug)"
	@echo "  run-debug    - Runs Debug version"
	@echo "  run-release  - Runs Release version"

run: run-debug

run-debug: debug
	$(DEBUG_TARGET)

run-release: release
	$(RELEASE_TARGET)

# PHONY directive
.PHONY: all debug release clean install help run run-debug run-release