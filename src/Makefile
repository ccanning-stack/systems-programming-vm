include ../Makefile.inc

.SUFFIXES:

BUILDDIR  := build
COMMONDIR := ../common

SRCS := $(wildcard *.c)
BINS := $(patsubst %.c,$(BUILDDIR)/%,$(SRCS))
OBJS := $(patsubst %.c,$(BUILDDIR)/%.o,$(SRCS))

CPPFLAGS += -I$(COMMONDIR)

.PHONY: all clean
all: $(BINS)

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(COMMONDIR)/libspl.a:
	$(MAKE) -C $(COMMONDIR)

$(BUILDDIR)/%.o: %.c | $(BUILDDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%: $(BUILDDIR)/%.o $(COMMONDIR)/libspl.a
	$(CC) $< $(COMMONDIR)/libspl.a -o $@

clean:
	$(RM) -r $(BUILDDIR)
	$(RM) -f *.o
	$(RM) -f $(notdir $(SRCS:.c=))
