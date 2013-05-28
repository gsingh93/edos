MODE=${1:-k}
DEBUG=$2

QEMU=qemu-system-i386
FLAGS=

if [[ $2 == d ]]; then
	FLAGS+="-s -S"
fi

if [[ $MODE == k ]]; then
	$QEMU $FLAGS -kernel out/kernel.bin
elif [[ $MODE == c ]]; then
	$QEMU $FLAGS -cdrom out/gulbuntu.iso
else
	echo "Invalid mode"
fi