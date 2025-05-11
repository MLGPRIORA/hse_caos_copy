# ----------  Makefile  ----------
# Компилятор и флаги
CC       := gcc
CFLAGS   := -Wall -Wextra -O2
PICFLAGS := -fPIC                 # для объектов, попадающих в .so
LDFLAGS  := -L. -Wl,-rpath,'$$ORIGIN'

# Имена артефактов
STATIC_LIB  := libfredjohn.a
SHARED_LIB  := libbillsam.so
TARGET      := solution

# Списки исходников / объектов
STATIC_SRCS := fred.c john.c
STATIC_OBJS := $(STATIC_SRCS:.c=.o)

SHARED_SRCS := bill.c sam.c
SHARED_OBJS := $(SHARED_SRCS:.c=.o)

MAIN_SRC    := solution.c
MAIN_OBJ    := $(MAIN_SRC:.c=.o)

# ----------  цели ----------

.PHONY: all clean run
all: $(TARGET)

# Главный бинарник
$(TARGET): $(MAIN_OBJ) $(STATIC_LIB) $(SHARED_LIB)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJ) $(LDFLAGS) -lfredjohn -lbillsam -lm

# Статическая библиотека (fred + john)
$(STATIC_LIB): $(STATIC_OBJS)
	@echo "  AR  $@"
	$(AR) rcs $@ $^

# Динамическая библиотека (bill + sam)
$(SHARED_LIB): $(SHARED_OBJS)
	@echo "  LD  $@"
	$(CC) -shared -o $@ $^ -lm

# Общие правила для объектов
%.o: %.c lib.h
	@echo "  CC  $<"
	$(CC) $(CFLAGS) $(PICFLAGS) -c $< -o $@

# ----------  вспомогательные цели ----------

run: $(TARGET)          # ./make run → запустить программу
	LD_PRELOAD= ./$(TARGET)

clean:
	rm -f *.o *.a *.so $(TARGET)
# ------------------------------------------
