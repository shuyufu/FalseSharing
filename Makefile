all:
	gcc -Wall -DLEVEL1_DCACHE_LINESIZE=4 main.c -lpthread -o no_align
	gcc -Wall -DLEVEL1_DCACHE_LINESIZE=`getconf LEVEL1_DCACHE_LINESIZE` main.c -lpthread -o align

clean:
	rm -f align no_align
