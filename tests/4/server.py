import os
import mmap

if __name__ == '__main__':
    if os.path.exists("/tmp/my_file"):
        os.remove("/tmp/my_file")
    fd = os.open("/tmp/my_file", os.O_CREAT | os.O_RDWR)
    print(fd)
    assert fd > 0
    os.ftruncate(fd, 512 * 1024 * 1024)  # 512 MB
    mm = mmap.mmap(fd, 0, flags=mmap.MAP_SHARED)
    print(len(mm))
    print("Filling memory map")
    mm.write(b'\xFF' * len(mm))
    print("Done")

    input("Press Enter to continue...")

    mm.close()
    os.close(fd)
    print("Server end")
