CXXFLAGS += -I..
CXXFLAGS += -std=c++11 -O0 -g -fpermissive
LDFLAGS  +=

SRC := \
	monitorable_active_object.cpp \
	local_active_object.cpp \
	abstract_active_object.cpp \

OBJ :=  $(SRC:.cpp=.o)
TARGETS :=  example

all: $(TARGETS)

example: example.o $(OBJ)
	@echo "Linking $@"
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) -f $(TARGETS) $(OBJ) *.o
