CXX = g++
CXXFLAGS = -std=c++11 -I/usr/local/include



BUILDDIR = build/build-fitter

SRCDIR1 = /home/lieuwe/Documents/Software/HybridProcessor/src/fitter-blastwave
# SRCDIR2 = /home/lieuwe/Documents/Software/HybridProcessor/src
# SRCDIR3 = /home/lieuwe/CERN_ROOT/build/include
# SRCDIR4 = /home/lieuwe



# SRCS1 = $(SRCDIR1)/Main.cpp 
# SRCS2 = $(SRCDIR2)/Histogram1D.cpp $(SRCDIR2)/Histogram2D.cpp $(SRCDIR2)/StatisticsContainer.cpp $(SRCDIR2)/Messenger.cpp $(SRCDIR2)/Utilities.cpp

# OBJS1 = $(BUILDDIR)/Main.o
# OBJS2 = $(BUILDDIR)/Histogram1D.o $(BUILDDIR)/Histogram2D.o $(BUILDDIR)/StatisticsContainer.o $(BUILDDIR)/Messenger.o $(BUILDDIR)/Utilities.o
# SRCS3 = $(SRCDIR3)/TH1.h
# OBJS1 = $(SRCS1:$(SRC1)/%.cpp=$(BUILDDIR)/%.o)
# OBJS2 = $(SRCS2:$(SRC2)/%.cpp=$(BUILDDIR)/%.o)
# OBJS = $(OBJS1) $(OBJS2)
# SRCS = $(SRCS1) $(SRCS2)

SRCS1 = $(wildcard $(SRCDIR1)/*.cpp)
OBJS1 = $(patsubst $(SRCDIR1)/%.cpp,$(BUILDDIR)/%.o,$(SRCS1))

TARGET = fitter

# ROOTLIBS := $(shell root-config --cflags --libs --evelibs) 
# GSLLIBS := $(shell gsl-config --cflags --libs)
# LIBS := $(ROOTLIBS) $(GSLLIBS)
LDFLAGS = -L/usr/local/lib -lboost_math_tr1


# OBJS3 := $(SRCS3:$(SRCDIR))

.PHONY: all clean

all: $(TARGET)

# $(TARGET): $(OBJS1) $(OBJS2)
# 	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

# Rule to compile source files into object files for src1

# $(BUILDDIR)/%.o: $(SRCDIR1)/%.cpp
# 	@mkdir -p $(BUILDDIR)
# 	$(CXX) $(CXXFLAGS) -I$(SRCDIR3) -c $< -o $@
$(TARGET): $(OBJS1)
	$(CXX) -o $(TARGET) $(OBJS1) $(LDFLAGS)

# Rule to compile the source files
$(BUILDDIR)/%.o: $(SRCDIR1)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# $(BUILDDIR)/%.o: $(SRCDIR2)/%.cpp
# 	@mkdir -p $(BUILDDIR)
# 	$(CXX) $(CXXFLAGS) -I$(SRCDIR3) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET)

