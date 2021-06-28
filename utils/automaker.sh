#
# !/bin/bash
#

make depend

cp .depend Makefile.tmp

sed -i 's/^\s//g' Makefile.tmp
sed -i 's/src/\$(SRCDIR)/g' Makefile.tmp
sed -i 's/include\$(INCLUDEDIR)/g' Makefile.tmp
sed -i 's/examples/\$(EXAMPLESDIR)/g' Makefile.tmp
sed -i 's/^\(\w\)/\$(BINDIR)\/\1/g' Makefile.tmp
sed -i 's/\(\w\)\s\([^\]\)/\1 \\\n\2/g' Makefile.tmp
sed -i 's/\$(BINDIR)/\t\$(CC) \$(CFLAGS) -o \$@ -c \$<\n\n\$(BINDIR)/g' Makefile.tmp

exit 0
