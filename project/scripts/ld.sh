set -x

ld \
	-dynamic-linker       \
	/lib64/ld-linux-x86-64.so.2       \
	-o        \
	project1        \
	/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crt1.o        \
	/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crti.o        \
	/usr/lib/gcc/x86_64-linux-gnu/5/crtbegin.o        \
	-L/usr/lib/gcc/x86_64-linux-gnu/5       \
	-L/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu       \
	-L/usr/lib/gcc/x86_64-linux-gnu/5/../../../../lib       \
	-L/lib/x86_64-linux-gnu       \
	-L/lib/../lib       \
	-L/usr/lib/x86_64-linux-gnu       \
	-L/usr/lib/../lib       \
	-L/usr/lib/gcc/x86_64-linux-gnu/5/../../..        \
	-Map        \
	project1.map        \
	-L`pwd`           \
	-lproject1        \
	-lc       \
	/usr/lib/gcc/x86_64-linux-gnu/5/crtend.o        \
	/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crtn.o
