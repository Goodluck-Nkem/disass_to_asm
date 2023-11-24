NAME=disass2asm
#DIR=${PREFIX}/local/bin
DIR=.

install:
	gcc -g -std=gnu11 -o $(DIR)/$(NAME) $(wildcard *.c)

run: install
	${DIR}/${NAME}

debug: install
	lldb ${DIR}/${NAME}

uninstall: clean

clean:
	rm -f $(DIR)/$(NAME)

