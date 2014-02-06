# Makefile IO
SRC_DIR=../
include $(SRC_DIR)Makefile.common

TARGETMCDTOOL=mcdTool
MAINMCDTOOL=mcdToolMain

CPPFLAGS += $(SHARED_CPPFLAGS)
LDFLAGS  += $(SHARED_LDFLAGS) $(SENSORS_LDFLAGS)
LDLIBS   += $(SENSORS_LDLIBS) -lMyConfigParser

#oggetti
LOCALOBJ := $(patsubst %$(SRCSUFFIX), %.o,$(shell find . -name "*$(SRCSUFFIX)" -and -not -name "$(MAIN)$(SRCSUFFIX)" -and -not -name "$(MAINMCDTOOL)$(SRCSUFFIX)"))

MAINOBJ=$(patsubst %$(SRCSUFFIX), %.o,$(MAIN)$(SRCSUFFIX))

MCDTOOLOBJ=$(patsubst %$(SRCSUFFIX), %.o,$(MAINMCDTOOL)$(SRCSUFFIX))

OBJ+=$(LOCALOBJ)


#Objects Section
%.o:%.cpp
	$(CC) -c $(CPPFLAGS) -o  $@  $^

lib%.a:
	$(AR) cr $@ $^

.PHONY: all main clean 

all: lib main tool;
	strip $(TARGET)
	strip $(TARGETMCDTOOL)

lib:libIO.a
libIO.a: $(OBJ)

main: $(TARGET)
$(TARGET) : $(OBJ) $(MAINOBJ) 
	$(CC) -o $(TARGET) $(OBJ) $(MAINOBJ) $(LDFLAGS) $(LDLIBS)

tool : $(TARGETMCDTOOL)
$(TARGETMCDTOOL)	: $(OBJ) $(MCDTOOLOBJ)
	$(CC) -o $(TARGETMCDTOOL) $(OBJ) $(MCDTOOLOBJ) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f *.o 
	rm -f $(TARGET) 
	rm -f $(TARGETMCDTOOL)
	rm -f *.a
	rm -f *~
