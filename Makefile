#Global Makefile

ROOTDIR = .
nKERNELVERSION=1_0_2
SRCDIR = $(ROOTDIR)/src
BINDIR = $(ROOTDIR)/bin
BACKUPDIR = ../$(ROOTDIR)/BACKUP
REMOTEBACKUPDIR=/media/nsfire/Backup/
DOCSDIR = $(ROOTDIR)/Docs
COMPONENTS= Sensors \
	IO \
	Communication \
	3D \
	WXVTKInterface \
	Actuators \
	HI \


EXE = prova

PREFIX_DIR?=/usr/local

.PHONY: all clean backup docs #install exes

all:
	cd $(SRCDIR)/ && $(MAKE) $@

clean:
	cd $(SRCDIR)/ && $(MAKE) $@
	rm -f *~
	rm -rf $(DOCSDIR)/html
	rm -f  $(SRCDIR)/Headers/*~

backup:	clean
	zip -r $(BACKUPDIR)/Project_`date +%Y_%m_%d_%Hh`_nKernel_$(nKERNELVERSION).zip ./; \
# 	sudo mount -t smbfs -o username=milo,password=milo,rw,dmask=777 //isaac/Backup $(REMOTEBACKUPDIR); \
	cp -f $(BACKUPDIR)/Project_`date +%Y_%m_%d_%Hh`_nKernel_$(nKERNELVERSION).zip $(REMOTEBACKUPDIR); \
	#tar -cvjf $(BACKUPDIR)/Project_`date +%m_%d_%Y_%Hh`.tar.bz2 ./*

docs:	
	doxygen  tesi_doxygen.cfg
	
#install: 
#	if ! (cd $(SRCDIR)/HI && $(MAKE) $@); \
#	then \
#	exit -1; \
#	fi \
#	done
	
#exe:
#	$(BINDIR)/$(EXE)
	
