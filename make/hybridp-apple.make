CXX = clang++


OMP_PATH = /opt/homebrew/opt/libomp
JSON_PATH = /opt/homebrew/opt/nlohmann-json

CXXFLAGS = -std=c++17 -Xpreprocessor -fopenmp
LDFLAGS = -L$(OMP_PATH)/lib -lomp
INCLUDE = -I$(OMP_PATH)/include -I$(JSON_PATH)/include
# echo $(CXXFLAGS)

BUILDDIR = build/build-hybridp
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

# SRCS = src/Main.cpp
# OBJS = build/Main.o

TARGET = hybridp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET)
