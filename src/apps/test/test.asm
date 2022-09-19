[bits 64]
global    _start

section   .text
_start:   
    mov       rax, 1                  ; system call for write
    mov       rdi, 1                  ; file handle 1 is stdout
    mov       rsi, message            ; address of string to output
    mov       rdx, 13                 ; number of bytes
    int 0x80                           ; invoke operating system to do the write
    ret

section   .data
message:  db        "Hello, World", 10      ; note the newline at the end
