section .data
    const1 dq 2.0
    const2 dq 6.0

section .text
; this function is analogue of 
; double f3(double x) and returns
; 1 / (2 - x) + 6 value:
global f3
f3:
    push ebp
    mov ebp, esp
    fld1
    fld qword [const1]; st0 == 2
    fld qword [ebp + 8]; st0 == x, st1 == 2
    fsubp; st1 == 2 - x, stack is popped
    fdivp; st1 == 1 / (2 - x), stack is popped
    fld qword [const2]; st0 == 6, st1 == 1 / (2 - x)
    faddp; st1 == 1 / (2 - x) + 6, stack is popped
    mov esp, ebp
    pop ebp
    ret