PROJECT_NAME=client
DEFS+=-D_GNU_SOURCE=1 -D_REENTRANT
INCLUDES+=-I$(INCLUDE_DIR)/libruputils -I$(INCLUDE_DIR)/libpollManager
LIBS+=-L$(LIB_DIR)


CFLAGS+=-g -c -Wall 
LDFLAGS+=-lruputils -lpollManager


OBJS = rupSock.o

include $(MAKE_DIR)/global.mak