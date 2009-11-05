PROJECT_NAME=client
DEFS+=-D_GNU_SOURCE=1 -D_REENTRANT
INCLUDES+=-I$(INCLUDE_DIR)/libruputils -I$(INCLUDE_DIR)/libpollManager -I$(INCLUDE_DIR)/librupSock
LIBS+=-L$(LIB_DIR)


CFLAGS+=-g -c -Wall 
LDFLAGS+=-lruputils -lpollManager -lrupSock


OBJS = 

include $(MAKE_DIR)/global.mak