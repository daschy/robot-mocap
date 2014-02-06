#Makefile Actuators

SRC_DIR=../
include $(SRC_DIR)Makefile.common

CPPFLAGS += $(WX_CPPFLAGS) $(VTK_CPPFLAGS) $(SHARED_CPPFLAGS)
LDFLAGS  += $(WX_LDFLAGS)  $(VTK_LDFLAGS) \
			$(3D_LDFLAGS) $(SENSORS_LDFLAGS) $(SHARED_LDFLAGS) $(WXVTKINTERFACE_LDFLAGS) $(IO_LDFLAGS) $(COMM_LDFLAGS)
LDLIBS   += $(WX_LDLIBS)   $(VTK_LDLIBS) \
			$(3D_LDLIBS) $(SENSORS_LDLIBS) $(WXVTKINTERFACE_LDLIBS) $(IO_LDLIBS) $(COMM_LDLIBS)


#oggetti
LOCALOBJ := $(patsubst %$(SRCSUFFIX), %.o,$(shell find . -name "*$(SRCSUFFIX)" -and -not -name "$(MAIN)$(SRCSUFFIX)"))

MAINOBJ=$(patsubst %$(SRCSUFFIX), %.o,$(MAIN)$(SRCSUFFIX))
 
OBJ += $(LOCALOBJ) ../WXVTKInterface/Frame3D.o 


# implementation
%.o:%.cpp
	$(CC) -c $(CPPFLAGS) -o  $@  $^

lib%.a:
	$(AR) cr $@ $^

.PHONY: all clean main lib

all: lib main;
	strip $(TARGET)


lib:libActuators.a
libActuators.a: $(LOCALOBJ)

main: $(TARGET)
$(TARGET) : $(OBJ) $(MAINOBJ)
	$(CC) -o $(TARGET) $(OBJ) $(MAINOBJ) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f *.o 
	rm -f $(TARGET) 
	rm -f *.a
	rm -f *~
	

