import socket
import mmap
import os

if __name__ == '__main__':
    with socket.socket(socket.AF_UNIX, socket.SOCK_STREAM) as s:
        s.connect(("127.0.0.1", 8888))
        s.sendall(b"Hello")
        data = s.recv(1024)

    print(f"Received {data!r}")

    fd = int.from_bytes(data, 'little')
    print(fd)

    mm = mmap.mmap(fd, 0, flags=mmap.MAP_SHARED)
    msg = b"Bye World!\0"
    mm[0:len(msg)] = msg

    print(mm[0:50])
    input("Press Enter to continue...")
    print(mm[0:50])

    mm.close()
