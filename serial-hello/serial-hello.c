#include <efi.h>
#include <efilib.h>

#define PORT 0x3f8   /* COM1 */

static inline
void outb(unsigned short port, unsigned char val)
{
    asm volatile("outb %0, %1"
                  : : "a"(val), "Nd"(port));
}

static inline
unsigned char inb(unsigned short port)
{
    unsigned char ret;
    asm volatile("inb %1, %0"
                  : "=a"(ret) : "Nd"(port));
    return ret;
}

int is_transmit_empty() {
   return inb(PORT + 5) & 0x20;
}
 
void write_serial(char a) {
   while (is_transmit_empty() == 0);
 
   outb(PORT, a);
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
  InitializeLib(ImageHandle, SystemTable);

  write_serial('h');
  write_serial('e');
  write_serial('l');
  write_serial('l');
  write_serial('o');
  write_serial('!');
  
  return EFI_SUCCESS;
}

