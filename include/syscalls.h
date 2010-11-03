#ifndef __syscalls_h__
#define __syscalls_h__

/**
    List the calls the user can make
**/
#define WRITE_SYSCALL_ID 0
#define READ_SYSCALL_ID 1
#define UPDATE_SCREEN_SYSCALL_ID 2
#define REFRESH_SCREEN_SYSCALL_ID 3

size_t write(int fileDescriptor, const void* buffer, size_t count){

size_t read(int fileDescriptor, const void* buffer, size_t count){

#endif
