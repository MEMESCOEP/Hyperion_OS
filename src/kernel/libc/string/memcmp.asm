section .text
global memcmp
memcmp:
    mov rcx, rdx
    repe cmpsb
    je .equal

    mov al, byte [rdi-1]
    sub al, byte [rsi-1]
    movsx rax, al
    jmp .done

  .equal:
    xor eax, eax

  .done:
    ret