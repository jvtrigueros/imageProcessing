#!/bin/bash
#File: makefile

BINARY	=	ImageProcessor
CFLAGS	=	-g	
SOURCES =	main.c	\
			imageIO.c					
OBJECTS = $(SOURCES:.c=.o)
$(BINARY): $(OBJECTS)
	gcc $(OBJECTS) -o $(BINARY)
%.d:	%.c
	rm	-f	$@;	gcc	-MM	$<	>	$@
include	$(SOURCES:.c=.d)
.PHONY:	clean
clean:
	rm -f $(OBJECTS)
	rm -f *.d
	rm -f $(BINARY)
