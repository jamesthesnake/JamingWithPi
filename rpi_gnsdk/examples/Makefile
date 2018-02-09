
CC=gcc
CFLAGS=-Wall
LDFLAGS=

INCLUDE_PATH=../include
LIB_PATH=../lib

INCLUDE=-I$(INCLUDE_PATH)/gnsdk -I$(INCLUDE_PATH)/gcsl
LIBS=$(LIB_PATH)/gnsdk/libgnsdk_manager.so.3.2.0 $(LIB_PATH)/gnsdk/libgnsdk_link.so.3.2.0 $(LIB_PATH)/gnsdk/libgnsdk_acr.so.3.2.0 $(LIB_PATH)/gnsdk/libgnsdk_dsp.so.3.2.0 $(LIB_PATH)/gnsdk/libgnsdk_storage_sqlite.so.3.2.0 $(LIB_PATH)/gnsdk/libgnsdk_video.so.3.2.0 $(LIB_PATH)/gnsdk/libgnsdk_epg.so.3.2.0 $(LIB_PATH)/gnsdk/libgnsdk_musicid.so.3.2.0 $(LIB_PATH)/gnsdk/libgnsdk_lookup_fplocal.so.3.2.0

EXECUTABLE=main
SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) $(EXECUTABLE)

.c.o: 
	$(CC) $(CFLAGS) -c $(INCLUDE) $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LIBS)
