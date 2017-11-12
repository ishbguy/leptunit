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
LIB_LDFLAGS := -coverage -Wall -shared
EXE_LDFLAGS :=
TST_LDFLAGS := -coverage -Wall -lm -l$(PRO) -L.
CFLAGS := -coverage -g -Wall -c
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
$(LIB) : $(LIB_OBJ)
	$(CC) $(LIB_LDFLAGS) -o $@ $^

.PHONY : test
test : $(TST)
$(TST) : $(LIB) $(TST_OBJ)
	$(CC) $(TST_LDFLAGS) -o $@ $(TST_OBJ)

.PHONY : cov
cov : $(COV)
$(COV) : $(SRC)
	$(CC) $(COVFLAGS) -o $@ $^
	./$@
	$(COVT) $(SRC)

%.o : %.$(LNG)
	$(CC) $(CFLAGS) -o $@ $<

.PHONY : clean
clean :
	$(RM) $(OUT) $(OBJ) $(COV) $(COV_OBJ)
