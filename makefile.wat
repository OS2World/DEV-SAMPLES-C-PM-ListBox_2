# makefile.wat - wmake / OpenWatcom build for DEV-SAMPLES-C-PM-ListBox_2
#
# Tools used:
#   Compile: wcc386
#   Link:    wlink
#   Resource: wrc
#   Make:    wmake

SRC = src
BIN = bin-wat

all : $(BIN)\lstbox2.exe

$(BIN)\lstbox2.exe : $(BIN)\lstbox2.obj $(BIN)\lstbox2.res $(SRC)\lstbox2.lnk
	wlink system os2v2_pm name $(BIN)\lstbox2.exe op q op maxe=25 &
	    file { $(BIN)\lstbox2.obj } @$(SRC)\lstbox2.lnk
	wrc -q $(BIN)\lstbox2.res $(BIN)\lstbox2.exe

$(BIN)\lstbox2.obj : $(SRC)\lstbox2.c $(SRC)\lstbox2.h
	if not exist $(BIN) md $(BIN)
	wcc386 -bt=os2 -q -Ot -wx -I$(SRC) $(SRC)\lstbox2.c -fo=$(BIN)\lstbox2.obj

$(BIN)\lstbox2.res : $(SRC)\lstbox2.rc $(SRC)\lstbox2.h
	if not exist $(BIN) md $(BIN)
	wrc -r -I$(SRC) $(SRC)\lstbox2.rc -fo=$(BIN)\lstbox2.res

clean : .SYMBOLIC
	if exist $(BIN)\lstbox2.obj del $(BIN)\lstbox2.obj
	if exist $(BIN)\lstbox2.res del $(BIN)\lstbox2.res
	if exist $(BIN)\lstbox2.exe del $(BIN)\lstbox2.exe
