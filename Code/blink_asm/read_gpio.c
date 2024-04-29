#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define GPIO_BASE 0xFE200000  // Adjust as per the datasheet
#define GPIO_PUP_PDN_CNTRL_REG1_OFFSET 0xE4  // Offset for GPIO_PUP_PDN_CNTRL_REG1

int main() {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("Failed to open /dev/mem");
        return -1;
    }

    volatile unsigned int *gpio = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
    if (gpio == MAP_FAILED) {
        perror("Failed to mmap");
        close(fd);
        return -1;
    }

    unsigned int reg_value = gpio[(GPIO_PUP_PDN_CNTRL_REG1_OFFSET / sizeof(unsigned int))];
    printf("GPIO_PUP_PDN_CNTRL_REG1: %08x\n", reg_value);

    munmap((void*)gpio, getpagesize());
    close(fd);
    return 0;
}

