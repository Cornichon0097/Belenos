# ============================== Variables ============================== #
# ----------------------------- Directories ----------------------------- #
# Build dir.
BUILDDIR = build
# Lib dir.
LIBDIR = lib
# Examples dir.
TESTDIR = test

# -------------------------------- Files -------------------------------- #
# Cmake files.
CMAKELISTS = CMakeLists.txt \
             $(LIBDIR)/CMakeLists.txt \
             $(TESTDIR)/CMakeLists.txt

# C files.
CFILES = $(shell ls $(LIBDIR)/src/*.c)

# Include files.
IFILES = $(shell ls $(LIBDIR)/include/belenos/*.h)

# Main target.
#TARGET = $(BUILDDIR)/lib/libbelenos.a # Default main target.
TARGET = $(BUILDDIR)/$(TESTDIR)/sample.out

# Target files (can be empty).
TARGETFILES = $(TESTDIR)/sample.c

# ========================== Targets and rules ========================== #
# ----------------------------- Main target ----------------------------- #
# Default target.
all: $(TARGET)

.PHONY: all

# ----------------------------- Main rules ------------------------------ #
# Main target rules.
$(TARGET): $(BUILDDIR) \
           $(CFILES) \
           $(IFILES) \
           $(TARGETFILES) \
           $(BUILDDIR)/Makefile
	cd $(BUILDDIR) && make

# Build dir Makefile rules.
$(BUILDDIR)/Makefile: $(CMAKELISTS)
	cd $(BUILDDIR) && cmake ..

# Build dir rules.
$(BUILDDIR):
	mkdir $@

# ----------------------------- Other rules ----------------------------- #
# Default run target.
run: all
	./$(TARGET)

# Default clean target.
clean:
	cd $(BUILDDIR) && make clean

# Rebuild target.
mrproper: clean all

# Full clean target.
maintainer-clean:
	rm -rf $(BUILDDIR)

.PHONY: run \
        clean \
        mrproper \
        maintainer-clean
