section .text
global memmove
memmove:
    mov rcx, rdx
    mov rax, rdi

    cmp rdi, rsi
    ja .copy_backwards

    rep movsb
    jmp .done

  .copy_backwards:
    lea rdi, [rdi+rcx-1]
    lea rsi, [rsi+rcx-1]
    std
    rep movsb
    cld

  .done:
    ret