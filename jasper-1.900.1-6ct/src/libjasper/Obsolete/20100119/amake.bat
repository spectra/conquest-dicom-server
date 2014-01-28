set path=c:\lang\ms8amd64\bin
set include=c:\lang\ms8amd64\include;\quirt\comps\exe\dgate;\quirt\comps\dll\cqdicom
set lib=c:\lang\ms8amd64\lib

cl -Iinclude -DJAS_WIN_MSVC_BUILD -MD -O2 -c jasperlib.c
copy jasperlib.obj \quirt\comps\exe\dgate\ms8amd64
