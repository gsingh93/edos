MODE=${1:-k}

if [[ $MODE == k ]]; then
qemu-system-i386 -kernel out/kernel.bin
elif [[ $MODE == c ]]; then
	qemu-system-i386 -cdrom out/gulbuntu.iso
else
	echo "Invalid mode"
fi