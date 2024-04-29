#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

//#define GPIO_BASE 0xFE200000  // Adjust as per the datasheet
//#define GPIO_BASE 0x7e2000e8  // Adjust as per the datasheet
//#define GPIO_BASE 0x47e2000e8  // Adjust as per the datasheet
//#define GPIO_BASE 0xc02000e8  // Adjust as per the datasheet
//#define GPIO_BASE 0x4c02000e8  // Adjust as per the datasheet
#define GPIO_BASE 0xFE200000  // Adjust as per the datasheet
//#define GPIO_BASE 0xFE200000  // Adjust as per the datasheet
//#define GPIO_BASE 0xFE200000  // Adjust as per the datasheet

#define GPIO_PUP_PDN_CNTRL_REG1_OFFSET 0xE8  // Offset for GPIO_PUP_PDN_CNTRL_REG1


void print_all() {
	uint32_t *v1 = 0xfe200000;
	printf("0xfe200000: %x", v1);	
}


int main(int argc, char argv[]) {

    if (argc < 2) {
	    printf("Using default address\n");
    }
    // TODO
    // int newadd = atoi(argv[0])

    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("Failed to open /dev/mem");
        return -1;
    }

    volatile uint32_t *gpio = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
    if (gpio == MAP_FAILED) {
        perror("Failed to mmap");
        close(fd);
        return -1;
    }
    
    printf("The mapped pointer gpio is: %x\n\n", gpio);

    volatile uint32_t *reg = gpio + (GPIO_PUP_PDN_CNTRL_REG1_OFFSET / sizeof(uint32_t));

    while (1) {
        // Read and print the current value of the register
        uint32_t reg_value = *reg;
        printf("Current GPIO_PUP_PDN_CNTRL_REG1: %08x\n", reg_value);
	print_all();
	sleep(1);
        // Set the register to 0xFFFFFFFF
        *reg = 0xFFFFFFFF;
        // Read and print the new value of the register
        reg_value = *reg;
        printf("New GPIO_PUP_PDN_CNTRL_REG1: %08x\n", reg_value);

        // Set the register to 0x0
        *reg = 0x0;
        // Wait for one second
        sleep(1);
    }

    munmap((void*)gpio, getpagesize());
    close(fd);
    return 0;
}

