PROJECT_NAME=rupSock
DEFS+=-D_GNU_SOURCE=1 -D_REENTRANT
INCLUDES+=-I$(INCLUDE_DIR)/libruputils
LIBS+=-L$(LIB_DIR)


CFLAGS+=-g -c -Wall 
LDFLAGS+=-lruputils


OBJS = 

include $(MAKE_DIR)/global.mak