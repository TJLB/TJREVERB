#include <libserialport.h>
#include <stdio.h>
#include <unistd.h>

#define BAUD_RATE   19200
#define BUFF_SIZE   512

unsigned char replay_array[] =
{0xff,0xff,0xff,0xc0,0x00,0xff,0xff,0xff,0x82,0xff,0xff,0xff,0xa0,0xff,0xff,0xff,0xa8,0xff,0xff,0xff,0xa8,0x68,0x40,0x60,0xff,0xff,0xff,0x9c,0xff,0xff,0xff,0x9e,0xff,0xff,0xff,0x86,0xff,0xff,0xff,0x82,0xff,0xff,0xff,0x98,0xff,0xff,0xff,0x98,0x60,0xff,0xff,0xff,0xae,0xff,0xff,0xff,0x92,0xff,0xff,0xff,0x88,0xff,0xff,0xff,0x8a,0x62,0x40,0x62,0xff,0xff,0xff,0xae,0xff,0xff,0xff,0x92,0xff,0xff,0xff,0x88,0xff,0xff,0xff,0x8a,0x64,0x40,0x63,0x03,0xff,0xff,0xff,0xf0,0x73,0x69,0x7f,0x7f,0x69,0x73,0x20,0x68,0x65,0x6d,0x6d,0x6f,0xff,0xff,0xff,0xc0};

struct sp_port *port;
char *serial_port_name;

void
write_array()
{
    enum sp_return ret = sp_nonblocking_write(port, replay_array, sizeof replay_array);
    if (ret != SP_OK)
        fprintf(stderr, "Unable to write to serial port %s\n", serial_port_name);
}

void 
print_buffer(unsigned char *byte_buff, int num_read) {
    for (int i = 0; i < num_read; i++)
        printf("%02x ", byte_buff[i]);
}

void
print_usage(char *command)
{
    fprintf(stderr, "Usage: %s <serial device>\n", command);
}

void
print_banner()
{
    puts("       TJREVERB CubeSat 2018              ");
    puts(" ______   _____  _____   _________  ___   ");
    puts("/_  __/_ / / _ \\/ __/ | / / __/ _ \\/ _ )");
    puts(" / / / // / , _/ _/ | |/ / _// , _/ _  |  ");
    puts("/_/  \\___/_/|_/___/ |___/___/_/|_/____/  ");
    puts("");
    puts("Thomas Jefferson HS & George Mason Univ.  ");
    printf("Version 0.1 compiled %s %s\n", __DATE__, __TIME__);
}
int
main(int argc, char **argv)
{
    unsigned char byte_buff[BUFF_SIZE] = {0};

    int bytes_waiting = 0;
    int num_read = 0;
    
    print_banner();

    if (argc < 2) {
        print_usage(argv[0]);
        return -1;
    }

    serial_port_name = argv[1]; // WARNING, No error checking here

    enum sp_return ret = sp_get_port_by_name(serial_port_name, &port);
    if (ret != SP_OK) {
        fprintf(stderr, "Unable to get serial port %s\n", serial_port_name);
        return -1;
    }

    ret = sp_open(port,SP_MODE_READ);
    if (ret != SP_OK) {
        fprintf(stderr, "Unable to open serial port %s\n", serial_port_name);
        return -1;
    }

    ret = sp_set_baudrate(port,BAUD_RATE);
    if (ret == SP_OK) {
        fprintf(stderr, "Unable to set the baud rate to: %d\n", BAUD_RATE);
        return -1;
    }

    while(1) {
        bytes_waiting = sp_input_waiting(port);
        if (bytes_waiting > 0) {
            num_read = sp_nonblocking_read(port,byte_buff, sizeof byte_buff);
            print_buffer(byte_buff,num_read);
        }
    }

    return 0;
}
