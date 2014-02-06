#Global Makefile

ROOTDIR = ..
SRCDIR = $(ROOTDIR)/src
CONFIGDIR = $(SRCDIR)/Config
COMPONENTS= Sensors \
	IO \
	Communication \
	3D \
	WXVTKInterface \
	HI \
	
	#Actuators \
	

EXE = prova

PREFIX_DIR?=/usr/local

.PHONY: all clean backup docs #install exes

all:
	for dir in $(COMPONENTS); do \
	if ! (cd $(SRCDIR)/$$dir && $(MAKE) $@); \
	then \
	exit -1; \
	fi \
	done
	cp -f ./HI/prova ./
	
clean:
	for dir in $(COMPONENTS); do \
	if ! (cd $(SRCDIR)/$$dir && $(MAKE) $@); \
	then \
	exit -1; \
	fi \
	done
	rm -f *~
	rm -f  $(SRCDIR)/Headers/*~
	rm -f $(CONFIGDIR)/*~
	rm -f $(CONFIGDIR)/*/*~

clean3d:
	(cd $(SRCDIR)/3D && $(MAKE) clean);
	(cd $(SRCDIR)/WXVTKInterface && $(MAKE) clean);
	(cd $(SRCDIR)/Actuators && $(MAKE) clean);
	(cd $(SRCDIR)/HI && $(MAKE) clean);

cleanwxvtk:
	(cd $(SRCDIR)/WXVTKInterface && $(MAKE) clean);
	(cd $(SRCDIR)/Actuators && $(MAKE) clean);
	(cd $(SRCDIR)/HI && $(MAKE) clean);

cleansens:
	(cd $(SRCDIR)/Sensors  && $(MAKE) clean);
	(cd $(SRCDIR)/IO && $(MAKE) clean);
	
cleancomm:
	(cd $(SRCDIR)/Communication  && $(MAKE) clean);
	(cd $(SRCDIR)/HI && $(MAKE) clean);

cleanact:
	(cd $(SRCDIR)/Actuators  && $(MAKE) clean);
	(cd $(SRCDIR)/HI && $(MAKE) clean);
cleanio:
	(cd $(SRCDIR)/IO && $(MAKE) clean);
	(cd $(SRCDIR)/HI && $(MAKE) clean);

cleancfg:
	rm -f $(CONFIGDIR)/*~
	rm -f $(CONFIGDIR)/*/*~

#install: 
#	if ! (cd $(SRCDIR)/HI && $(MAKE) $@); \
#	then \
#	exit -1; \
#	fi \
#	done
	
#exe:
#	$(BINDIR)/$(EXE)
	