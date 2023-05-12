import os
import mmap
import socket

if __name__ == '__main__':
    fd = os.memfd_create("test", flags=os.O_RDWR)
    print(fd)
    assert fd > 0
    os.ftruncate(fd, 256)
    mm = mmap.mmap(fd, 0, flags=mmap.MAP_SHARED)
    msg = b"Hello World!\0"
    mm[0:len(msg)] = msg

    with socket.socket(socket.AF_UNIX, socket.SOCK_STREAM) as s:
        s.bind("/tmp/geds.sock")
        s.listen()
        print("Waiting for connection...")
        conn, addr = s.accept()
        with conn:
            print(f"Connected by {addr}")
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                print(data)
                res = fd.to_bytes(4, 'little')
                print(f"Sending: {res}")
                conn.sendall(res)

    input("Press Enter to continue...")

    print(mm[0:50])
    mm[0:len(msg)] = msg

    input("Press Enter to continue...")
    print(mm[0:50])

    mm.close()
    os.close(fd)
