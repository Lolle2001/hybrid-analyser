CXX = g++


OMP_PATH = /opt/homebrew/opt/libomp
JSON_PATH = /opt/homebrew/opt/nlohmann-json

CXXFLAGS = -std=c++17 -Xpreprocessor -fopenmp -I$(OMP_PATH)/include -L$(OMP_PATH)/lib -lomp -I$(JSON_PATH)/include

# echo $(CXXFLAGS)

BUILDDIR = build
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

# SRCS = src/Main.cpp
# OBJS = build/Main.o

TARGET = hybridp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET)
