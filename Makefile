FILES = ./build/kernel.asm.o  ./build/kernel.o ./build/memory/memory.o ./build/idt/idt.o ./build/idt/idt.asm.o ./build/io/io.asm.o	./build/memory/heap.o ./build/memory/kheap.o ./build/io/keyboard.o ./build/idt/pic.o ./build/io/mouse.o ./build/memory/paging.o
INCLUDES = -I./src
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

all: ./bin/boot.bin ./bin/kernel.bin 
	rm -rf ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=512 count=100 >> ./bin/os.bin

./bin/kernel.bin: $(FILES)
	i686-elf-ld -g -relocatable $(FILES) -o ./build/kernelfull.o
	i686-elf-gcc $(FLAGS) -T ./src/linker.ld -o ./bin/kernel.bin -ffreestanding -O0 -nostdlib ./build/kernelfull.o

./bin/boot.bin: ./src/boot/boot.asm
	nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin

./build/kernel.asm.o: ./src/kernel.asm
	nasm -f elf -g ./src/kernel.asm -o ./build/kernel.asm.o

./build/kernel.o: ./src/kernel.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/kernel.c -o ./build/kernel.o

./build/memory/memory.o: ./src/memory/memory.c
	i686-elf-gcc $(INCLUDES)/memory $(FLAGS) -std=gnu99 -c ./src/memory/memory.c -o ./build/memory/memory.o

./build/idt/idt.o: ./src/idt/idt.c
	i686-elf-gcc $(INCLUDES)/idt $(FLAGS) -std=gnu99 -c ./src/idt/idt.c -o ./build/idt/idt.o

./build/idt/idt.asm.o: ./src/idt/idt.asm
	nasm -f elf -g ./src/idt/idt.asm -o ./build/idt/idt.asm.o

./build/memory/heap.o: ./src/memory/heap.c
	i686-elf-gcc $(INCLUDES)/memory $(FLAGS) -std=gnu99 -c ./src/memory/heap.c -o ./build/memory/heap.o

./build/memory/kheap.o: ./src/memory/kheap.c
	i686-elf-gcc $(INCLUDES)/memory $(FLAGS) -std=gnu99 -c ./src/memory/kheap.c -o ./build/memory/kheap.o

./build/io/io.asm.o:
	nasm -f elf -g ./src/io/io.asm -o ./build/io/io.asm.o

./build/io/keyboard.o:	./src/io/keyboard.c
	i686-elf-gcc $(INCLUDES)/io $(FLAGS) -std=gnu99 -c ./src/io/keyboard.c -o ./build/io/keyboard.o

./build/idt/pic.o: ./src/idt/pic.c
	i686-elf-gcc $(INCLUDES)/idt $(FLAGS) -std=gnu99 -c ./src/idt/pic.c -o ./build/idt/pic.o

./build/io/mouse.o: ./src/io/mouse.c
	i686-elf-gcc $(INCLUDES)/io $(FLAGS) -std=gnu99 -c ./src/io/mouse.c -o ./build/io/mouse.o

./build/memory/paging.o: ./src/memory/paging.c
	i686-elf-gcc $(INCLUDES)/memory $(FLAGS) -std=gnu99 -c ./src/memory/paging.c -o ./build/memory/paging.o

clean:
	rm -rf ./bin/boot.bin
	rm -rf ./bin/kernel.bin
	rm -rf ./bin/os.bin
	rm -rf $(FILES)
	rm -rf ./build/kernelfull.o