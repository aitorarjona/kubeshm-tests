import mmap
import os

if __name__ == '__main__':
    fd = os.open("/tmp/my_file", os.O_RDWR)
    mm = mmap.mmap(fd, 0, flags=mmap.MAP_SHARED)

    print("Iterating over memory map")
    b = mm.read(65536)
    while b != b'':
        b = mm.read(65536)
    print("Done")

    input("Press Enter to continue...")

    print("Closing memory map")
    mm.close()
    print("Client end")
