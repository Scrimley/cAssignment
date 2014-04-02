clean:
# Remove all derived files from the directory – i.e. compiler output such as exe-
# cutables and .o files.
	/bin/rm -f dictionary.o
#/bin/rm -f d_run.c
d_run:
# Makes an executable program from the given test program d run.c. The exe-
# cutable must be called d run.
	gcc -Wall d_run.c dictionary.o avl_any.o -o d_run
zip:
# Creates a zipped, tar file containing the files: dictionary.h, dictionary.c,
# d run.c, README, makefile, and any other source files that your implementation
# requires. The zipped tar file must be called p12345678.tar.gz where the “p-
# number” (p...) is your actual p-number.
	tar -cvzf p12197868.tar.gz dictionary.h dictionary.c d_run.c README makefile
# NB You can easily check if your zip target is working by (a) running make zip;
# (b) copying the tar.gz file to /tmp; (c) changing directory to /tmp; (d) decom-
# pressing the archive (tar xvzf ...); and finally, (e) building the application
# (make all). If the program builds and then runs successfully then you have
# created a portable archive of your application.
all:
# Builds the library and d run executable. Normally this will refer simply to the
# d run target.
	make clean
	gcc -c avl_any.c
	gcc -c dictionary.c
	make d_run
