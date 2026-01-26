include ../Makefile.inc

BIN = hex2int
SRCS = hex2int.c
OBJS = $(SRCS:.c=.o)

COMMONDIR = ../common

CPPFLAGS += -I$(COMMONDIR)

all: $(BIN)

$(BIN): $(OBJS) $(COMMONDIR)/libspl.a
	$(CC) $(OBJS) $(COMMONDIR)/libspl.a -o $@

$(COMMONDIR)/libspl.a:
	$(MAKE) -C $(COMMONDIR)

clean:
	$(RM) $(OBJS) $(BIN)
