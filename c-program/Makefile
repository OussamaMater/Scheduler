final: main.o helpers.o
	gcc main.o helpers.o -o final

main.o: main.c utils/process.h utils/helpers.h src/fifo.h src/rr.h
	gcc -c main.c src/fifo.c src/rr.c

helpers.o: utils/helpers.c utils/process.h
	gcc -c utils/helpers.c

clean:
	rm *.o final

install:
	@if [ -w "/root" ]; then\
		echo "\033[0;32mwriteable";\
	else\
		echo "\033[0;31mYou don't have permission";\
		echo "Executing as the root\033[0m";\
		sudo cp final /usr/local/bin;\
		echo "\033[0;32mInstalled Sucessfuly!";\
	fi\

