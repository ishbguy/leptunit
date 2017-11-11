# project
PRO := leptunit
LNG := c

# output
EXE :=
LIB := lib$(PRO).so
TST := test-$(PRO)
OUT := $(EXE) $(LIB) $(TST)

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

# tools
ifeq ($(LNG), c)
	CC := gcc
else
	CC := g++
endif
LIB_LDFLAGS := -Wall -shared
EXE_LDFLAGS :=
TST_LDFLAGS := -Wall -lm -l$(PRO) -L.
CFLAGS := -Wall -c
RM := rm -f

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
test : $(LIB) $(TST)
$(TST) : $(TST_OBJ)
	$(CC) $(TST_LDFLAGS) -o $@ $^

%.o : %.$(LNG)
	$(CC) $(CFLAGS) -o $@ $<

.PHONY : clean
clean :
	$(RM) $(OUT) $(OBJ)
