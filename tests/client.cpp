#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>

const int MEM_PAGE_SIZE = 4096;

int main(int argc, char *argv[]) {
    int fd = open("/tmp/my_file.txt", O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

    char *buffer =
        reinterpret_cast<char *>(mmap(nullptr, MEM_PAGE_SIZE, PROT_WRITE, MAP_SHARED, fd, 0));

    std::cout << "Buffer content: " << buffer << std::endl;

    strcpy(buffer, "Bye World!\0");

    std::cout << "Buffer content: " << buffer << std::endl;

    std::cout << "Wait for other processes to access the buffer..." << std::endl;
    std::cin.get();

    std::cout << "Buffer content: " << buffer << std::endl;

    std::cout << "Bye!" << std::endl;

    return 0;
}
