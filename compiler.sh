nasm -f bin bootloader.asm -o bootloader.bin
nasm kernel_entry.asm -f elf -o kernel_entry.o
nasm interrupt.asm -f elf -o interrupt.o
nasm keyboardHandlerStub.asm -f elf -o keyboardHandlerStub.o
nasm -f bin filldisk.asm -o filldisk.bin


i386-elf-gcc -ffreestanding -m32 -nostdlib -g -c kernel.c -o kernel.o
i386-elf-gcc -ffreestanding -m32 -nostdlib -g -c basic.c -o basic.o
i386-elf-gcc -ffreestanding -m32 -nostdlib -g -c block.c -o block.o
i386-elf-gcc -ffreestanding -m32 -nostdlib -g -c block_movement.c -o block_movement.o
i386-elf-gcc -ffreestanding -m32 -nostdlib -g -c pit.c -o pit.o
i386-elf-gcc -ffreestanding -m32 -nostdlib -g -c font.c -o font.o

i386-elf-ld -o full_kernel.bin -Ttext 0x1000 kernel_entry.o keyboardHandlerStub.o pit.o interrupt.o font.o kernel.o basic.o block.o block_movement.o  --oformat binary



cat bootloader.bin full_kernel.bin > everything.bin

cat everything.bin filldisk.bin > OS.bin

rm everything.bin
rm bootloader.bin
rm full_kernel.bin
rm kernel_entry.o
rm kernel.o
rm filldisk.bin
rm pit.o
rm interrupt.o
rm block.o
rm block_movement.o
rm basic.o

qemu-system-i386 -device sb16, -drive format=raw,file="OS.bin",index=0,if=floppy -m 512M
