section .text
; this function is analogue of 
; double f1(double x) and returns
; ln(x) value:
global f1
f1:
    ; prologue:
    push ebp
    mov ebp, esp
    ; main body:
    fldln2; st0 == ln(2) = 1/log2(e)
    fld qword [ebp + 8]; st0 == x, st1 = ln(2)
    fyl2x; st1 == log2(x) / log2(e) = ln(x) and the stack is popped
    ; epilogue:
    mov esp, ebp
    pop ebp
    ret