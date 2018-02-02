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

RM := rm -rf
COVT := gcov
COV_FLAGS := -coverage -g -Wall
INFO_FILE := $(PRO).info
REPORT_DIR := $(PRO)-test-report
LCOV := lcov
LCOV_FLAGS := --capture --directory . --output-file $(INFO_FILE) --test-name $(PRO)
GEN_HTML := genhtml
GEN_HTML_FLAGS := $(INFO_FILE) --output-directory $(REPORT_DIR) \
	--title "Test For $(PRO)" --show-details --legend

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
	$(CC) $(COV_FLAGS) -o $@ $^
	./$@
	$(COVT) $(SRC)
	$(LCOV) $(LCOV_FLAGS)
	$(GEN_HTML) $(GEN_HTML_FLAGS)

.PHONY : clean
clean :
	$(RM) $(OUT) $(OBJ) $(COV) $(COV_OBJ) $(INFO_FILE) $(REPORT_DIR)
