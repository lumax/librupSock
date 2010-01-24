PROJECT_NAME=librupSock
MAJOR=1
MINOR=0
VERSION=$(MAJOR).$(MINOR)

DEFS+=-D_GNU_SOURCE=1 -D_REENTRANT
INCLUDES+=-I$(INCLUDE_DIR)/libruputils -I$(INCLUDE_DIR)/libpollManager
LIBS+=

CFLAGS+=-g -c -Wall -fPIC
LDFLAGS+= -lruputils -lpollManager -shared -Wl #,-soname,$(PROJECT_NAME).so.$(MAJOR)

OBJS = rupSock.o

EXE_ANHANG = .so.$(VERSION)

include $(MAKE_DIR)/global.mak
