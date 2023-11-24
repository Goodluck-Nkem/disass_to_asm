.data

.bss

.text

.global int_to_str
.p2align 4
.section .text.int_to_str
int_to_str:
int_to_str_0:     endbr64 
int_to_str_4:     cmp    $0xb,%esi
int_to_str_7:     jbe    int_to_str_58
int_to_str_9:     push   %r12
int_to_str_11:    push   %rbp
int_to_str_12:    push   %rbx
int_to_str_13:    mov    %rdi,%r12
int_to_str_16:    mov    %esi,%ebx
int_to_str_18:    mov    %edx,%ebp
int_to_str_20:    mov    %edx,%edi
int_to_str_22:    call   abs_u32
int_to_str_27:    mov    %eax,%edx
int_to_str_29:    mov    %ebx,%esi
int_to_str_31:    mov    %r12,%rdi
int_to_str_34:    call   word_to_str
int_to_str_39:    test   %ebp,%ebp
int_to_str_41:    js     int_to_str_48
int_to_str_43:    pop    %rbx
int_to_str_44:    pop    %rbp
int_to_str_45:    pop    %r12
int_to_str_47:    ret    
int_to_str_48:    movb   $0x2d,-0x1(%rax)
int_to_str_52:    lea    -0x1(%rax),%rax
int_to_str_56:    jmp    int_to_str_43
int_to_str_58:    mov    $0x0,%eax
int_to_str_63:    ret    



.global word_to_str_ex
.p2align 4
.section .text.word_to_str_ex
word_to_str_ex:
word_to_str_ex_0:     endbr64 
word_to_str_ex_4:     mov    %ecx,%eax
word_to_str_ex_6:     shr    $0x6,%al
word_to_str_ex_9:     lea    -0x1(%rax),%r8d
word_to_str_ex_13:    cmp    $0x1,%r8b
word_to_str_ex_17:    jbe    word_to_str_ex_33
word_to_str_ex_19:    cmp    $0x3,%al
word_to_str_ex_21:    je     word_to_str_ex_42
word_to_str_ex_23:    test   %al,%al
word_to_str_ex_25:    je     word_to_str_ex_51
word_to_str_ex_27:    mov    $0x0,%eax
word_to_str_ex_32:    ret    
word_to_str_ex_33:    movzbl %cl,%ecx
word_to_str_ex_36:    call   hex_to_str
word_to_str_ex_41:    ret    
word_to_str_ex_42:    movzbl %cl,%ecx
word_to_str_ex_45:    call   bin_to_str
word_to_str_ex_50:    ret    
word_to_str_ex_51:    call   word_to_str
word_to_str_ex_56:    ret    



.section .note.GNU-stack
