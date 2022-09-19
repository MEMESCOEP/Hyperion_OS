section .text
global memset
memset:
    push rdi
    mov rax, rsi
    mov rcx, rdx
    rep stosb
    pop rax
    ret
