CC       := gcc
CFLAGS   := -Wall -Wextra -O2
PICFLAGS := -fPIC
LDFLAGS  := -L. -Wl,-rpath,'$$ORIGIN'

STATIC_LIB  := libfredjohn.a
SHARED_LIB  := libbillsam.so
TARGET      := solution

STATIC_SRCS := fred.c john.c
STATIC_OBJS := $(STATIC_SRCS:.c=.o)

SHARED_SRCS := bill.c sam.c
SHARED_OBJS := $(SHARED_SRCS:.c=.o)

MAIN_SRC    := solution.c
MAIN_OBJ    := $(MAIN_SRC:.c=.o)


.PHONY: all clean run
all: $(TARGET)

$(TARGET): $(MAIN_OBJ) $(STATIC_LIB) $(SHARED_LIB)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJ) $(LDFLAGS) -lfredjohn -lbillsam -lm

$(STATIC_LIB): $(STATIC_OBJS)
	@echo "  AR  $@"
	$(AR) rcs $@ $^

$(SHARED_LIB): $(SHARED_OBJS)
	@echo "  LD  $@"
	$(CC) -shared -o $@ $^ -lm

%.o: %.c lib.h
	@echo "  CC  $<"
	$(CC) $(CFLAGS) $(PICFLAGS) -c $< -o $@


run: $(TARGET)
	LD_PRELOAD= ./$(TARGET)

clean:
	rm -f *.o *.a *.so $(TARGET)
