CC=gcc
CFLAGS=-Wall -std=c99 -g -O2 -I./include
LDFLAGS=
OBJDIR=./obj
BINDIR=./bin
SRCDIR=./src
TESTDIR=./tests
INCDIR=./include

OBJS=$(OBJDIR)/mgfn_core.o $(OBJDIR)/mgfn_key.o $(OBJDIR)/mgfn_utils.o \
	$(OBJDIR)/main.o

TARGET=$(BINDIR)/a.out

.PHONY: all clean dir rebuild

all: dir $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(OBJS:.o=.d)

clean:
	rm -f $(OBJS) $(TARGET) $(OBJDIR)/*.d

dir:
	@mkdir -p $(OBJDIR) $(BINDIR)

rebuild: clean all

run:
	(cd bin && ./a.out)

debug:
	(cd bin && gdb a.out)

leak: 
	(cd bin && valgrind --leak-check=full --show-leak-kinds=all ./a.out)