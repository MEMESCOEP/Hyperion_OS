section .text
global memcpy
memcpy:
    mov rcx, rdx
    mov rax, rdi
    rep movsb
    ret