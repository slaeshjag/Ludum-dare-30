# Project: ludum dare #30
include config.mk
MAKEFLAGS	+=	--no-print-directory

TOPDIR		=	$(shell pwd)
export TOPDIR

.PHONY: all tools lib install strip clean

all:
	@echo " [INIT] bin/"
	@$(MKDIR) bin/
	@echo " [ CD ] src/"
	+@make -C src/
	@echo " [ CD ] res/"
	+@make -C res/
	
	@echo "Build complete."
	@echo 

clean:
	@echo " [ RM ] bin/"
	+@$(RM) bin/
	@echo " [ CD ] src/"
	+@make -C src/ clean
	@echo " [ CD ] res/"
	+@make -C res/ clean
	@echo
	@echo "Source tree cleaned."
	@echo

strip:
	@echo " [STRP] bin/"
	@strip $(LIB)
