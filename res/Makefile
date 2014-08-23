# Project: LD30
include $(TOPDIR)/config.mk

.PHONY: all clean

all:
	@echo " [LDMZ] res/testmap.tmx"
	@darnit-tmxconv testmap.tmx testmap.ldmz
	@echo "Done."

clean:
	@echo " [ RM ] rm res/testmap.ldmz"
	@rm -f testmap.ldmz
