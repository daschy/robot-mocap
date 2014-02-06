# Makefile CommInterface

SRC_DIR=../
include $(SRC_DIR)Makefile.common

CPPFLAGS += $(SHARED_CPPFLAGS) $(SERIAL_CPPFLAGS)
LDFLAGS  += $(ROBOT_LDFLAGS) $(SHARED_LDFLAGS) $(SERIAL_LDFLAGS)
LDLIBS   += -lcgMessages

#oggetti
LOCALOBJ := $(patsubst %$(SRCSUFFIX), %.o,$(shell find . -name "*$(SRCSUFFIX)" -and -not -name "$(MAIN)$(SRCSUFFIX)"))

ROBOTSHAREDOBJ= $(SHARED_DIR)/cgConnectionTCP.o \
		$(SHARED_DIR)/cgConnectionUnix.o \

MAINOBJ=$(patsubst %$(SRCSUFFIX), %.o,$(MAIN)$(SRCSUFFIX))

OBJ += $(ROBOTSHAREDOBJ) \
	$(LOCALOBJ) \


#Objects Section
%.o:%.cpp
	$(CC) -c $(CPPFLAGS) -o  $@  $^

lib%.a:
	$(AR) cr $@ $^

.PHONY: all main clean 

all: lib main;
	strip $(TARGET)

lib:libComm.a
libComm.a: $(OBJ)

main: $(TARGET)
$(TARGET) : $(OBJ) $(MAINOBJ)
	$(CC) -o $(TARGET) $(OBJ) $(MAINOBJ) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f *.o 
	rm -f $(TARGET) 
	rm -f *.a
	rm -f *~
