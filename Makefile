# Simple AlphaBeta Pruning makefile
# Link: https://docs.microsoft.com/en-us/cpp/build/nmake-reference
CC=cl
#CFLAGS=/c /EHsc
#Compile with debug info
CFLAGS=/c /EHsc /Zi
LINK=link
#LFLAGS=
#Link with debug info
LFLAGS= /DEBUG
ODIR=bin
EXE=SimpleABP.exe

all: $(ODIR)\$(EXE)

.cpp{$(ODIR)}.obj: 
	$(CC) $(CFLAGS) $** /Fo$@

$(ODIR)\$(EXE): $(ODIR)\main.obj $(ODIR)\SimpleAlphaBeta.obj $(ODIR)\ElapsedTimer.obj
	$(LINK) $** $(LFLAGS) /out:$@

clean:
	@IF EXIST *.pdb (del *.pdb)
	@IF EXIST bin\*.obj (del bin\*.obj)
	@IF EXIST bin\*.pdb (del bin\*.pdb)
	@IF EXIST bin\*.exe (del bin\*.exe)
	@IF EXIST bin\*.asm (del bin\*.asm)
	@IF EXIST bin\*.ilk (del bin\*.ilk)