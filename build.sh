clear
nasm -f elf32 boot.asm -o boot.o
gcc -m32 -c kernel.c -o kernel.o -fno-stack-protector
gcc -m32 -c ./src/print.c -o ./src/print.o
ld -m elf_i386 -T link.ld -o ./bin/kernel.bin boot.o kernel.o ./src/print.o
qemu-system-x86_64 -kernel ./bin/kernel.bin

# Cleaning
rm ./kernel.o
rm ./boot.o

read -p "Delete kernel? [Y/n]: " delkernel

if [ "$delkernel" = "y" ] || [ "$delkernel" = "Y" ]; then
    rm ./bin/kernel.bin
fi