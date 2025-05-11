# ----------  Makefile for Task 1 (interposition edition)  ----------

# инструменты
CC      := gcc
AR      := ar
CFLAGS  := -Wall -Wextra -g -fPIC
LDFLAGS := -lm                              # math библиотека для john и sam

# цели-по-умолчанию
.PHONY: all
all: main

# ------------------------------------------------------------------
#  1.  Статическая библиотека fred+john  (link-time interposition)
# ------------------------------------------------------------------
STATIC_SRCS := fred.c john.c
STATIC_OBJS := $(STATIC_SRCS:.c=.o)
STATIC_LIB  := libfredjohn.a

$(STATIC_LIB): $(STATIC_OBJS)
	$(AR) rcs $@ $^                 # ar rcs … — традиционный способ собрать .a :contentReference[oaicite:2]{index=2}

# ------------------------------------------------------------------
#  2.  Разделяемая библиотека bill+sam  (подключаем math)
# ------------------------------------------------------------------
SHARED_SRCS := bill.c sam.c
SHARED_OBJS := $(SHARED_SRCS:.c=.o)
SHARED_LIB  := libbillsam.so

$(SHARED_LIB): $(SHARED_OBJS)
	$(CC) $(CFLAGS) -shared -o $@ $^ $(LDFLAGS)   # -fPIC в CFLAGS, -shared при линковке :contentReference[oaicite:3]{index=3}

# ------------------------------------------------------------------
#  3.  Библиотека-перехватчик для LD_PRELOAD (bill+sam)
# ------------------------------------------------------------------
PRELOAD_SRCS := preload_bill.c preload_sam.c
PRELOAD_OBJS := $(PRELOAD_SRCS:.c=.o)
PRELOAD_LIB  := libbillsam_preload.so

$(PRELOAD_LIB): $(PRELOAD_OBJS)
	$(CC) $(CFLAGS) -shared -o $@ $^

# ------------------------------------------------------------------
#  4.  Обёртки для fred и john (link-time interposition, --wrap)
# ------------------------------------------------------------------
WRAP_SRCS := wrap_fred.c wrap_john.c
WRAP_OBJS := $(WRAP_SRCS:.c=.o)
WRAP_FLAGS := -Wl,--wrap=fred -Wl,--wrap=john     # GNU ld wrap option :contentReference[oaicite:4]{index=4}

# ------------------------------------------------------------------
#  5.  Финальное приложение
# ------------------------------------------------------------------
main: main.o $(WRAP_OBJS) $(STATIC_LIB) $(SHARED_LIB)
	$(CC) $(WRAP_FLAGS) -o $@ $^ -L. -lfredjohn -lbillsam $(LDFLAGS)

# ------------------------------------------------------------------
#  6.  Стандартные шаблоны компиляции и «запуск с прелоадом»
# ------------------------------------------------------------------
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run
run: main $(PRELOAD_LIB)
	LD_PRELOAD=$(PWD)/$(PRELOAD_LIB) ./main     # load-time interposition via loader :contentReference[oaicite:5]{index=5}

.PHONY: clean
clean:
	rm -f *.o *.a *.so main
# ------------------------------------------------------------------
