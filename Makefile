LANG := c
OUT := libleptunit.so
SRC := $(shell ls *.$(LANG))
OBJ := $(subst .$(LANG),.o,$(SRC))

ifeq ($(LANG), c)
	CC := gcc
else
	CC := g++
endif
LDFLAGS := -shared
CFLAGS := -c
RM := rm -f

.PHONY : all
all : $(OUT)

$(OUT) : $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o : %.$(LANG)
	$(CC) $(CFLAGS) -o $@ $<

.PHONY : clean
clean :
	$(RM) $(OUT) $(OBJ)
