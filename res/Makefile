# Project: LD30
include $(TOPDIR)/config.mk

.PHONY: all clean

all:
	@echo " [LDMZ] res/splash.tmx"
	@darnit-tmxconv splash.tmx splash.ldmz
	@echo " [ CD ] res/levelpack"
	+@make -C levelpack/
	@echo "Done."
	@echo

clean:
	@echo " [ CD ] res/levelpack"
	+@make -C levelpack/ clean
	@echo "Done."
	@echo 
