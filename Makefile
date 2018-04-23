CC = gcc
CFLAGS = -fPIC  -fpermissive -lJTC -lpthread -ldl
INC = -I. -I/usr/include
LIBS_INCDIR = -L../../lib
LIBS = -lOB -lstdc++

SRC_CPP_FILE = ${@F:.o=.cpp}

.cpp.o:
	@echo ---------------------------------------------------------------
	@echo OBJECT $(@F)
	$(CC) -c $(CFLAGS) $(INC) $(SRC_CPP_FILE) -D_DEBUG
	@echo ---------------------------------------------------------------


SERVER_OBJS = server.o upTime.o upTime_skel.o



server: ${SERVER_OBJS}
	${CC} -o server ${CFLAGS} ${SERVER_OBJS}  ${LIBS}

CLIENT_OBJS = client.o upTime.o

client: ${CLIENT_OBJS}
	${CC} -o clients ${CFLAGS} ${CLIENT_OBJS}  ${LIBS}
