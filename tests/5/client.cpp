#include <cstring>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <sys/mman.h>

const int MEM_PAGE_SIZE = 4 * 1024; // 4 KB
//const int INITIAL_BUFFER_SIZE = MEM_PAGE_SIZE;
//const int INITIAL_BUFFER_SIZE = MEM_PAGE_SIZE * 32768; // 128 MB
const int INITIAL_BUFFER_SIZE = MEM_PAGE_SIZE * 65536; // 256 MB

int main(int argc, char *argv[]) {
    int fd = open("/tmp/my_file.txt", O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    char *mmap_ptr =
        reinterpret_cast<char *>(mmap(nullptr, INITIAL_BUFFER_SIZE, PROT_WRITE, MAP_SHARED, fd, 0));

    std::cout << "Buffer pointer: " << static_cast<void *>(&mmap_ptr) << std::endl;

//    memset(mmap_ptr + (INITIAL_BUFFER_SIZE / 2) - 30, '#', 60);
//    char my_char = *(mmap_ptr + (INITIAL_BUFFER_SIZE / 2) + 3);
//    memcpy(&my_char, , sizeof(my_char));
//    std::cout << "my_char: " << my_char << std::endl;

//    std::cout << "Buffer content: " << mmap_ptr << std::endl;
//
//    strcpy(mmap_ptr, "Bye World!\0");
//
//    std::cout << "Buffer content: " << mmap_ptr << std::endl;
//
//    std::cout << "Wait for other processes to access the buffer..." << std::endl;
//    std::cin.get();
//
//    std::cout << "Buffer content: " << mmap_ptr << std::endl;

//    std::cout << "Setting buffer with zeros..." << std::endl;
//    memset(mmap_ptr, '#', INITIAL_BUFFER_SIZE);
//    std::cout << "Done" << std::endl;

//    std::cout << "Press enter to continue..." << std::endl;
//    std::cin.get();
//
    std::cout << "Press enter to continue..." << std::endl;
    std::cin.get();

    std::cout << "memset first half of buffer" << std::endl;
    memset(mmap_ptr, '#', INITIAL_BUFFER_SIZE / 2);

    std::cout << "Press enter to continue..." << std::endl;
    std::cin.get();

    std::cout << "iterate second half of buffer" << std::endl;
    char* p = mmap_ptr + (INITIAL_BUFFER_SIZE / 2);
    char c;
    for (int i = 0; i < INITIAL_BUFFER_SIZE / 2; i++) {
        c = *p;
        p++;
    }

    std::cout << "Press enter to continue..." << std::endl;
    std::cin.get();

    int res = munmap(mmap_ptr, INITIAL_BUFFER_SIZE);
    if (res == -1) {
        perror("munmap");
        return -1;
    }
    std::cout << "munmap " << res << std::endl;

    res = close(fd);
    if (res == -1) {
        perror("close");
        return -1;
    }
    std::cout << "close " << res << std::endl;

    return 0;
}
