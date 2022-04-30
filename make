CC:=gcc
HW_DIR:=/home/mtm/public/2122b/ex1/
PATH: =tool/
OBJS:=RLEList.o $(PATH) AsciiArtTool.o $(PATH)main.o
EXEC:=AsciiArtTool
DEBUG_FLAG:=-DNDEBUG
COMP_FLAG:=-std=c99 -Wall -pedantic-errors -Werror -I/home/mtm/public/2122b/ex1 -Itool
$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $(OBJS) -o $0
RLEList.0:RLEList.c$CHW_DIR)RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*. c
$(PATH) Asci1ArtTool.o: $(PATH) AsciiArtTool.c $(PATH) AsciiArtTool.h $CHW_DIR)RLEL1st.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.C -0 $ (PATH) AsciiArtTool.o
$(PATH)main.o: $(PATH)main.c $(PATH) Asci1ArtTool.h $CHW_DIR)RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c -0 $(PATH)main.o
clean:
	TI -f $(OBJS) $ (EXEC)]
