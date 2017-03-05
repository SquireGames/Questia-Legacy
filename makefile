#-------------------
# Variables
#-------------------
CC         := g++ 
CFLAGS     := -std=c++11 -Wall -MMD -MP
DEBUGFLAGS := -g -DDEBUGMODE=1
LIB        := -L lib/SFML-2.4.2/lib -lsfml-audio -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system
SRCEXT     := cpp

SRCDIR     := src
INC        := -I include
TARGET      = bin/Questia
TARGET_D    = bin/Questia_debug
BUILDDIR   := build
BUILDDIR_D := build_debug

#-------------------
# Mode
#-------------------

ifneq "$(findstring ebug, $(MAKECMDGOALS))" ""
	TARGET    = $(TARGET_D)
	BUILDDIR := $(BUILDDIR_D)
	CFLAGS   += $(DEBUGFLAGS)
else
endif

#-------------------
# Dependant Variables
#------------------- 


ifeq ($(OS),Windows_NT)
	SOURCES := $(wildcard src/*.$(SRCEXT)) $(wildcard src/**/*.$(SRCEXT)) $(wildcard src/**/**/*.$(SRCEXT))\
	$(wildcard src/**/**/**/*.$(SRCEXT)) $(wildcard src/**/**/**/**/*.$(SRCEXT))\
	$(wildcard src/**/**/**/**/**/*.$(SRCEXT)) $(wildcard src/**/**/**/**/**/**/*.$(SRCEXT))
else
	SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
endif

TARGET_ALL   = $(TARGET)   $(TARGET_D)
BUILDDIR_ALL = $(BUILDDIR) $(BUILDDIR_D)

OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS    := $(OBJECTS:.o=.d)

#-------------------
# Build
#------------------- @echo $(SOURCES)

all: $(OBJECTS) $(TARGET)
default: release
Release: release
Debug: release
debug: release

release: $(TARGET)
$(TARGET): $(OBJECTS)
ifeq ($(OS),Windows_NT)
	-$(shell mkdir $(dir $@))
else
	@mkdir -p $(dir $@)
endif
	@echo " Linking..."
	$(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
ifeq ($(OS),Windows_NT)
	-$(shell mkdir $(dir $@))
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
else
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
endif

-include $(DEPS)

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR_ALL) $(TARGET_ALL)

cleanRelease:
	@echo " Cleaning Release...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

cleanDebug:
	@echo " Cleaning Debug...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR_D) $(TARGET_D)

	DEPS := $(SOURCES:.c=.d)

.c.d:
	$(CC) -o $< -MM $(CFLAGS)

.PHONY: clean
#------------
