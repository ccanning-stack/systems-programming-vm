include ../Makefile.inc
.SUFFIXES:
BUILDDIR  := build
COMMONDIR := ../common
SRCS := $(wildcard *.c)
BINS := $(patsubst %.c,$(BUILDDIR)/%,$(SRCS))
OBJS := $(patsubst %.c,$(BUILDDIR)/%.o,$(SRCS))
DEBUGDIR  := debug
DEBUGBINS := $(patsubst %.c,$(DEBUGDIR)/%,$(SRCS))
DEBUGOBJS := $(patsubst %.c,$(DEBUGDIR)/%.o,$(SRCS))
CPPFLAGS += -I$(COMMONDIR)
.PHONY: all clean debug clean-debug
all: $(BINS)
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)
$(COMMONDIR)/libspl.a:
	$(MAKE) -C $(COMMONDIR)
$(BUILDDIR)/%.o: %.c | $(BUILDDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
$(BUILDDIR)/%: $(BUILDDIR)/%.o $(COMMONDIR)/libspl.a
	$(CC) $< $(COMMONDIR)/libspl.a -o $@
debug: $(DEBUGBINS)
$(DEBUGDIR):
	@mkdir -p $(DEBUGDIR)
$(DEBUGDIR)/%.o: %.c | $(DEBUGDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -g -O0 -c $< -o $@
$(DEBUGDIR)/%: $(DEBUGDIR)/%.o $(COMMONDIR)/libspl.a
	$(CC) $< $(COMMONDIR)/libspl.a -o $@
clean-debug:
	$(RM) -r $(DEBUGDIR)
clean:
	$(RM) -r $(BUILDDIR)
	$(RM) -f *.o
	$(RM) -f $(notdir $(SRCS:.c=))
