CXXFLAGS += -I..
CXXFLAGS += -std=c++11 -O0 -g -fpermissive
LDFLAGS  +=

SRC := \
	abstract_active_object.cpp \
	active_object.cpp \
	active_object_control_block.cpp \
	active_object_system.cpp \
	local_active_object.cpp \
	monitorable_active_object.cpp \

OBJ :=  $(SRC:.cpp=.o)
TARGETS :=  example

all: $(TARGETS)

example: example.o $(OBJ)
	@echo "Linking $@"
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) -f $(TARGETS) $(OBJ) *.o
