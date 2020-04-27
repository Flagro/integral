section .data
    const1 dq -2.0
    const2 dq 14.0

section .text
; this function is analogue of 
; double f2(double x) and returns
; -2x + 14 value:
global f2
f2:
    ; prologue:
    push ebp
    mov ebp, esp
    ; main body:
    fld qword [const1]; st0 == -2
    fld qword [ebp + 8]; st0 == x, st1 == -2
    fmulp; st1 == -2x, stack is popped
    fld qword [const2]; st0 == 14, st1 = -2x
    faddp; st1 == -2x + 14, stack is popped
    ; epilogue:
    mov esp, ebp
    pop ebp
    ret