incdirs := inc
libdirs :=
libs    :=

include makefile-config

sources := main.cc utils.cc error.cc memory.cc unicode.cc
objects := ${sources:.cc=.o}

ifeq ($(words ${sources}), 0)
$(error No source files are provided!)
endif

${obj}/%.o: src/%.cc
	${compiler} ${incdirs} ${flags} -o $(call path,$@) $(call path,$^)

${bin}/program.exe: $(addprefix ${obj}/,${objects})
	${compiler} -o $(call path,$@) $(call path,$^) ${libdirs} ${libs}