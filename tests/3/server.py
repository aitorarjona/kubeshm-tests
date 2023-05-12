import os
import mmap

if __name__ == '__main__':
    if os.path.exists("/tmp/my_file"):
        os.remove("/tmp/my_file")
    fd = os.open("/tmp/my_file", os.O_CREAT | os.O_RDWR)
    print(fd)
    assert fd > 0
    os.ftruncate(fd, 64)
    mm = mmap.mmap(fd, 0, flags=mmap.MAP_SHARED)

    msg = b"Hello World!\0"
    mm[0:len(msg)] = msg
    print(mm[0:64])

    input("Press Enter to continue...")

    print(mm[0:64])
    msg = b"Hello from server pod\0"
    mm[0:len(msg)] = msg
    print(mm[0:64])

    input("Press Enter to continue...")
    print(mm[0:64])

    mm.close()
    os.close(fd)
