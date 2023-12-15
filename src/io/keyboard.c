#include "keyboard.h"

void keyboard_init(){
    // while(commandport.Read() & 0x1)
    //     dataport.Read();
    // commandport.Write(0xae); // activate interrupts
    // commandport.Write(0x20); // command 0x20 = read controller command byte
    // uint8_t status = (dataport.Read() | 1) & ~0x10;
    // commandport.Write(0x60); // command 0x60 = set controller command byte
    // dataport.Write(status);
    // dataport.Write(0xf4);

    // while(insb(KEYBOARD_COMMAND_PORT) & 0x1) insb(KEYBOARD_DATA_PORT);
    outb(KEYBOARD_COMMAND_PORT, 0xAE);
    // outb(KEYBOARD_COMMAND_PORT, 0xAD);
    // outb(KEYBOARD_COMMAND_PORT, 0x20);
    // uint8_t status = (insb(KEYBOARD_DATA_PORT) | 1) & ~0x01;
    // outb(KEYBOARD_COMMAND_PORT, 0x60);
    // outb(KEYBOARD_DATA_PORT, status);
    // outb(KEYBOARD_DATA_PORT, 0xf4);
}

uint8_t read_scan_code(){
    return insb(KEYBOARD_DATA_PORT);
}

void scan_code_to_action(uint8_t key){
     if(key < 0x80)
    {
        switch(key)
        {
            case 0x03: print_char('2', 15); break;
            case 0x02: print_char('1', 15); break;
            case 0x04: print_char('3', 15); break;
            case 0x05: print_char('4', 15); break;
            case 0x06: print_char('5', 15); break;
            case 0x07: print_char('6', 15); break;
            case 0x09: print_char('8', 15); break;
            case 0x08: print_char('7', 15); break;
            case 0x0A: print_char('9', 15); break;
            case 0x0B: print_char('0', 15); break;
            case 0x10: print_char('q', 15); break;
            case 0x11: print_char('w', 15); break;
            case 0x12: print_char('e', 15); break;
            case 0x13: print_char('r', 15); break;
            case 0x14: print_char('t', 15); break;
            case 0x15: print_char('z', 15); break;
            case 0x16: print_char('u', 15); break;
            case 0x17: print_char('i', 15); break;
            case 0x18: print_char('o', 15); break;
            case 0x19: print_char('p', 15); break;
            case 0x1E: print_char('a', 15); break;
            case 0x1F: print_char('s', 15); break;
            case 0x20: print_char('d', 15); break;
            case 0x21: print_char('f', 15); break;
            case 0x22: print_char('g', 15); break;
            case 0x23: print_char('h', 15); break;
            case 0x24: print_char('j', 15); break;
            case 0x25: print_char('k', 15); break;
            case 0x26: print_char('l', 15); break;
            case 0x2C: print_char('y', 15); break;
            case 0x2D: print_char('x', 15); break;
            case 0x2E: print_char('c', 15); break;
            case 0x2F: print_char('v', 15); break;
            case 0x30: print_char('b', 15); break;
            case 0x31: print_char('n', 15); break;
            case 0x32: print_char('m', 15); break;
            case 0x33: print_char(',', 15); break;
            case 0x34: print_char('.', 15); break;
            case 0x35: print_char('-', 15); break;
            case 0x1C: print_char('\n', 15); break;
            case 0x39: print_char(' ', 15); break;

            default:
            {
                print("KEYBOARD 0x");
                break;
            }
        }
    }
}