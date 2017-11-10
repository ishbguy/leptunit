PRO := leptunit
LNG := c
LIB := lib$(PRO).so
EXE :=
TST := test-$(PRO)
OUT := $(LIB) $(EXE) $(TST)
SRC := $(shell ls *.$(LNG))
OBJ := $(subst .$(LNG),.o,$(SRC))

ifeq ($(LNG), c)
	CC := gcc
else
	CC := g++
endif
LIB_LDFLAGS := -shared
EXE_LDFLAGS :=
TST_LDFLAGS := -lm -l$(PRO) -L.
CFLAGS := -c
RM := rm -f

.PHONY : all
all : $(OUT)

.PHONY : lib
lib : $(LIB)
$(LIB) : $(OBJ)
	$(CC) $(LIB_LDFLAGS) -o $@ $^

.PHONY : test
test : $(LIB) $(TST)
$(TST) : $(addsuffix .o,$(TST))
	$(CC) $(TST_LDFLAGS) -o $@ $<

%.o : %.$(LNG)
	$(CC) $(CFLAGS) -o $@ $<

.PHONY : clean
clean :
	$(RM) $(OUT) $(OBJ)
