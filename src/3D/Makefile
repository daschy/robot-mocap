# Makefile 3D
SRC_DIR=../
include $(SRC_DIR)Makefile.common

CPPFLAGS += $(VTK_CPPFLAGS) $(SHARED_CPPFLAGS)
LDFLAGS  += $(VTK_LDFLAGS) $(SHARED_LDFLAGS)
LDLIBS   += $(VTK_LDLIBS)


#oggetti
LOCALOBJ := $(patsubst %$(SRCSUFFIX), %.o,$(shell find . -name "*$(SRCSUFFIX)" -and -not -name "$(MAIN)$(SRCSUFFIX)"))

MAINOBJ=$(patsubst %$(SRCSUFFIX), %.o,$(MAIN)$(SRCSUFFIX))
 
OBJ += $(LOCALOBJ)

# implementation
%.o:%.cpp
	$(CC) -c $(CPPFLAGS) -o  $@  $^

lib%.a:
	$(AR) cr $@ $^

	
	
.PHONY: all clean main lib

all: lib main;
	strip $(TARGET)

lib:lib3D.a
lib3D.a: $(OBJ)

main: $(TARGET)
$(TARGET) : $(OBJ) $(MAINOBJ)
	$(CC) -o $(TARGET) $(OBJ) $(MAINOBJ) $(LDFLAGS) $(LDLIBS)
	
clean:
	rm -f *.o 
	rm -f $(TARGET) 
	rm -f *.a
	rm -f *~