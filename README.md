# DEV-SAMPLES-C-PM-ListBox_2

Sample PM program demonstrating a two-column owner-draw list box.

When `LS_OWNERDRAW` is specified as a list box style, the application must
provide `WM_MEASUREITEM` and `WM_DRAWITEM` processing.  This sample shows
how to split each item string on a blank character to render two columns
using `WinDrawText`.

The program opens a dialog window containing the owner-draw list box
populated with sample filename/description pairs.

## LICENSE
* BSD 3 Clauses

## COMPILE TOOLS
* yum install git gcc make libc-devel binutils watcom-wrc watcom-wlink-hll watcom-wcc

## PROJECT LAYOUT
```
src/                - Source files
  lstbox2.c         - Main program, FillCfgListBox, and dialog procedure
  lstbox2.h         - Defines (dialog/control IDs, MAX_ITEM_TEXT_LENGTH)
  lstbox2.rc        - Dialog resource (LS_OWNERDRAW list box)
  lstbox2.def       - Module definition (GCC linker)
  lstbox2.lnk       - wlink response file (OpenWatcom linker)
doc/                - Documentation
  lstbox2.txt       - Original LSTBOX.TXT by Guy Scharf
  lstbox2_notes.txt - Technique notes and history
img/                - Screenshots
bin-gcc/            - GCC/kLIBC build output
bin-wat/            - OpenWatcom build output
makefile.gcc        - GNU make rules for GCC build
makefile.wat        - wmake rules for OpenWatcom build
compile_gcc.cmd     - Run the GCC build
compile_wat.cmd     - Run the OpenWatcom build
```

## HOW TO COMPILE

**GCC / kLIBC:**
```
compile_gcc.cmd
```
Output: `bin-gcc\lstbox2.exe`. Build log: `make_gcc.out`.

**OpenWatcom:**
```
compile_wat.cmd
```
Output: `bin-wat\lstbox2.exe`. Build log: `make_wat.out`.

## AUTHORS
* Guy Scharf, Software Architects, Inc. (original fragment)
* Martin Iturbide (2026)

## CHANGE HISTORY
* 1.01 - 2026-09-07 - Source extracted from LSTBOX.TXT; completed into a full PM program with main(), FillCfgListBox(), dialog resource, and module def; dual GCC and OpenWatcom build support added.

## LINKS
* https://github.com/OS2World/DEV-SAMPLES-C-PM-ListBox2
