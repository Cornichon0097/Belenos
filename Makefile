BUILDDIR = build

TARGET = $(BUILDDIR)/examples/sample.out


all: $(TARGET)

$(TARGET): $(BUILDDIR) $(BUILDDIR)/Makefile
	cd $(BUILDDIR) && make

$(BUILDDIR):
	mkdir $@

$(BUILDDIR)/Makefile:
	cd $(BUILDDIR) && cmake ..


run: all
	./$(TARGET)

clean:
	cd $(BUILDDIR) && make clean

mrproper: clean all

maintainer-clean:
	rm -rf $(BUILDDIR)

.PHONY: all \
        run \
        clean \
        mrproper \
        maintainer-clean
