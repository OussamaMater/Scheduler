scheduler: main.o helpers.o fifo.o rr.o sjf.o srt.o pnp.o
	gcc main.o helpers.o fifo.o rr.o sjf.o srt.o pnp.o -o scheduler

main.o: main.c utils/helpers.h headers/fifo.h headers/rr.h headers/sjf.h headers/srt.h headers/pnp.h
	gcc -c main.c src/fifo.c src/rr.c src/sjf.c src/srt.c src/pnp.c

helpers.o: utils/helpers.c
	gcc -c utils/helpers.c

fifo.o:
	gcc -c src/fifo.c utils/helpers.c

rr.o:
	gcc -c src/rr.c utils/helpers.c

sjf.o:
	gcc -c src/sjf.c utils/helpers.c

srt.o:
	gcc -c src/srt.c utils/helpers.c

pnp.o:
	gcc -c src/pnp.c utils/helpers.c

clean:
	@rm *.o 2> /dev/null
	@echo "\033[0;32mCleaned object files!";\

install:
	@if [ -w "/usr/local/bin" ]; then\
		sudo cp scheduler /usr/local/bin;\
                echo "\033[0;32mInstalled Sucessfuly!";\
	else\
		echo "\033[0;31mYou don't have permission";\
		echo "Executing as the root\033[0m";\
		sudo cp scheduler /usr/local/bin;\
		echo "\033[0;32mInstalled Sucessfuly!";\
	fi\

