import socket
import mmap
import os

if __name__ == '__main__':
    fd = os.open("/tmp/my_file", os.O_RDWR)
    mm = mmap.mmap(fd, 0, flags=mmap.MAP_SHARED)

    msg = b"Bye World!\0"
    mm[0:len(msg)] = msg
    print(mm[0:64])

    input("Press Enter to continue...")

    print(mm[0:64])
    msg = b"Goodbye from client pod\0"
    mm[0:len(msg)] = msg
    print(mm[0:64])

    print("Closing memory map")
    mm.close()
    print("Client end")
