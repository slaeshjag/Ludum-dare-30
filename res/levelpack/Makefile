# Project: LD30
include $(TOPDIR)/config.mk

TMXFILES	=	$(wildcard *.tmx)
MAPFILES	=	$(TMXFILES:.tmx=.ldmz)
.PHONY: all clean

all: $(MAPFILES)
	@mkdir -p levels
	@cp levels.index levels/
	@echo " [LDI ] res/levelpack.ldi"
	@darnit-fsimage levels ../levelpack.ldi
	@echo "Done."

clean:
	@echo " [ RM ] rm res/levelpack/levels"
	@rm -rf levels/

%.ldmz: %.tmx
	@mkdir -p levels
	@echo " [LDMZ] res/levelpack/$<"
	@darnit-tmxconv $< levels/$@
