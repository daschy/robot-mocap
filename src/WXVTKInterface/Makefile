#Makefile WXVTKInterface
SRC_DIR=../
include $(SRC_DIR)Makefile.common

INTERFACE = wxVTKRenderWindowInteractor

CFLAGS   += $(WX_CFLAGS)   $(VTK_CFLAGS) $(SHARED_CPPFLAGS)
CPPFLAGS += $(WX_CPPFLAGS) $(VTK_CPPFLAGS) $(SHARED_CPPFLAGS)
LDFLAGS  += $(WX_LDFLAGS) $(VTK_LDFLAGS) $(3D_LDFLAGS) $(SHARED_LDFLAGS) $(IO_LDFLAGS)
LDLIBS   += $(WX_LDLIBS)   $(VTK_LDLIBS)   $(APP_LDLIBS) $(3D_LDLIBS) $(IO_LDLIBS)

LOCALOBJ := $(patsubst %$(SRCSUFFIX), %.o,$(shell find . -name "*$(SRCSUFFIX)" -and -not -name "$(INTERFACE)$(SRCSUFFIX)" -and -not -name "$(MAIN)$(SRCSUFFIX)"))

MAINOBJ=$(patsubst %$(SRCSUFFIX), %.o,$(MAIN)$(SRCSUFFIX))
 
 INTERFACEOBJ=$(patsubst %$(SRCSUFFIX), %.o,$(INTERFACE)$(SRCSUFFIX))
 
OBJ += $(LOCALOBJ) \
	$(INTERFACEOBJ)

%.o:%.cpp
	$(CC) -c $(CPPFLAGS) -o  $@  $^

lib%.a:
	$(AR) cr $@ $^


.PHONY: all clean lib main

all: lib main;
	strip $(TARGET)

lib:libwxVtkInterface.a
libwxVtkInterface.a: $(OBJ)

main: $(TARGET)
$(TARGET): $(OBJ) $(MAINOBJ)
	$(CC) -o $(TARGET) $(OBJ) $(MAINOBJ) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f *.o 
	rm -f $(TARGET) 
	rm -f *.a
	rm -f *~
