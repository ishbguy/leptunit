# project
PRO := leptunit
LNG := c

# output
EXE :=
LIB := lib$(PRO).so
TST := test-$(PRO)
OUT := $(EXE) $(LIB) $(TST)
COV := cov-$(TST)

# input
EXE_SRC :=
LIB_SRC := $(PRO).$(LNG)
TST_SRC := $(TST).$(LNG)
SRC := $(EXE_SRC) $(LIB_SRC) $(TST_SRC)

# object files
EXE_OBJ :=
LIB_OBJ := $(subst .$(LNG),.o,$(LIB_SRC))
TST_OBJ := $(subst .$(LNG),.o,$(TST_SRC))
OBJ := $(EXE_OBJ) $(LIB_OBJ) $(TST_OBJ)
COV_OBJ := $(shell ls *.gcno *.gcda *.gcov 2>/dev/null)

# tools
ifeq ($(LNG), c)
	CC := gcc
else
	CC := g++
endif
CFLAGS := -g -Wall -c

EXE_LDFLAGS :=
EXE_CFLAGS :=

LIB_LDFLAGS := -shared
LIB_CFLAGS := -fPIC -g -Wall

TST_LDFLAGS := -lm -L. -l$(PRO)
TST_CFLAGS := -g -Wall

RM := rm -f
COVT := gcov
COVFLAGS := -coverage -g -Wall

# targets
.PHONY : all
all : $(OUT)

.PHONY : exe
exe : $(EXE)
$(EXE) : $(EXE_OBJ)

.PHONY : lib
lib : $(LIB)
$(LIB) : $(LIB_SRC)
	$(CC) $(LIB_LDFLAGS) $(LIB_CFLAGS) -o $@ $^

.PHONY : test
test : $(TST)
$(TST) : $(LIB) $(TST_SRC)
	$(CC) $(TST_LDFLAGS) $(TST_CFLAGS) -o $@ $(TST_SRC)

.PHONY : cov
cov : $(COV)
$(COV) : $(SRC)
	$(CC) $(COVFLAGS) -o $@ $^
	./$@
	$(COVT) $(SRC)

.PHONY : clean
clean :
	$(RM) $(OUT) $(OBJ) $(COV) $(COV_OBJ)
