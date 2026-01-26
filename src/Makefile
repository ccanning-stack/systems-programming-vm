include ../Makefile.inc

BUILDDIR := build
COMMONDIR := ../common

SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=$(BUILDDIR)/%)
OBJS := $(SRCS:%.c=$(BUILDDIR)/%.o)

CPPFLAGS += -I$(COMMONDIR)

.PHONY: all clean

all: $(BINS)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(COMMONDIR)/libspl.a:
	$(MAKE) -C $(COMMONDIR)

$(BUILDDIR)/%.o: %.c | $(BUILDDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%: $(BUILDDIR)/%.o $(COMMONDIR)/libspl.a
	$(CC) $< $(COMMONDIR)/libspl.a -o $@

clean:
	$(RM) -r $(BUILDDIR)
