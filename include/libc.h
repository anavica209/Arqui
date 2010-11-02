#ifndef __libc_h__
#define __libc_h__

#define false 0
#define true 1

void write(int fileDescriptor, char* buffer, int size);
void read(int fileDescriptor, char* buffer, int size);

#endif //__libc_h__
