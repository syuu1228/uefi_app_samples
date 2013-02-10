/** @file
  This sample application bases on HelloWorld PCD setting 
  to print "UEFI Hello World!" to the UEFI Console.

  Copyright (c) 2006 - 2008, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials                          
  are licensed and made available under the terms and conditions of the BSD License         
  which accompanies this distribution.  The full text of the license may be found at        
  http://opensource.org/licenses/bsd-license.php                                            

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>

#define COM1_PORT	0x3f8
#define COM_DATA	0x0
#define COM_LSR		0x5

void outb(unsigned short port, unsigned char val)
{
	asm volatile("outb %0, %1"
		:: "a"(val), "Nd"(port));
}

unsigned char inb(unsigned short port)
{
	unsigned char ret;
	asm volatile("inb %1, %0"
		: "=a"(ret) : "Nd"(port));
	return ret;
}

void com1_putc(char a)
{
	while ((inb(COM1_PORT + COM_LSR) & 0x20) == 0)
		;
	outb(COM1_PORT + COM_DATA, a);
}

void com1_puts(char *str)
{
	char c;
	while ((c = *str)) {
		com1_putc(c);
		str++;
	}
}

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
	com1_puts("hello!");

	return EFI_SUCCESS;
}
