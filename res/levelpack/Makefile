# Project: LD30
include $(TOPDIR)/config.mk

.PHONY: all clean

all:
	@mkdir -p levels
	@echo " [LDMZ] res/levelpack/testmap.tmx"
	@darnit-tmxconv testmap.tmx levels/testmap.ldmz
	@echo " [LDMZ] res/levelpack/testmap2.tmx"
	@darnit-tmxconv testmap2.tmx levels/testmap2.ldmz
	@cp levels.index levels/
	@echo " [LDI ] res/levelpack.ldi"
	@darnit-fsimage levels ../levelpack.ldi
	@echo "Done."

clean:
	@echo " [ RM ] rm res/levelpack/levels"
	@rm -rf levels/
