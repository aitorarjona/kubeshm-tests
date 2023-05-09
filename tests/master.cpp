#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>

const int MEM_PAGE_SIZE = 4096;

int main(int argc, char *argv[]) {
    std::remove("/tmp/my_file.txt");

    int fd = open("/tmp/my_file.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

    posix_fallocate(fd, 0, MEM_PAGE_SIZE);

    char *buffer =
        reinterpret_cast<char *>(mmap(nullptr, MEM_PAGE_SIZE, PROT_WRITE, MAP_SHARED, fd, 0));

    memset(buffer, '\0', MEM_PAGE_SIZE);

    strcpy(buffer, "Hello World!\0");

    std::cout << "Buffer content: " << buffer << std::endl;

    std::cout << "Wait for other processes to access the buffer..." << std::endl;
    std::cin.get();

    std::cout << "Buffer content: " << buffer << std::endl;

    strcpy(buffer, ":)\0");

    int res = munmap(buffer, MEM_PAGE_SIZE);
    if (res == -1) {
        perror("munmap");
        return -1;
    }
}
