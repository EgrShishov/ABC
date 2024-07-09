section .data
    k: dq 0.0
    x: dq 0.0
    four: dq 4.0
    temp_result: dq 0.0
    result: dq 0.0

section .text
    global eval_y
    global count_s

eval_y:
    movsd qword [x], xmm0
    finit
    
    fldpi
    fld qword [four]
    fdiv
    fsin
    fld qword [x]
    fmul
    fcos
    fstp qword [temp_result]

    ;calculation of exp    
    fld qword [x]
    fldpi
    fld qword [four]
    fdiv
    fcos
    fmul
    fldl2e 
    fmul   
    fld1             

    fld st1
    fprem 
    f2xm1
    faddp st1, st0
    fscale
    fstp st1
    fld qword [temp_result]
    fmul
    fstp qword [rsp - 8]
    mov rdx, [rsp - 8]
    movq xmm0, rdx
    ret

count_s:
    movsd qword [x], xmm0 ;
    mov [k], rdi

    finit
    fild qword [k]
    fldpi
    fmul
    fld qword [four]
    fdiv
    fcos ; cos(k*pi/4)

 factorial:  
    fild qword [k]
    fdiv
    mov rcx, qword [k]
    dec rcx
    mov qword [k], rcx
    fstp qword [result]
    fld qword [result]
    cmp qword [k], 1
    jg factorial
    fstp qword [result]

    mov [k], rdi
    fild qword [k] ;power
    fld qword [x] ;base
    fyl2x ;Стек FPU теперь содержит: ST(0)=z
    fld st0 ;Создаем еще одну копию z
    frndint   ;Округляем ST(0)=trunc(z)        | ST(1)=z
    fxch st1;ST(0)=z                             | ST(1)=trunc(z)
    fsub st0,st1
    f2xm1  ;ST(1)=z, ST(0)=2**(z-trunc(z))-1
    fld1
    faddp  ;ST(1)=z, ST(0)=2**(z-trunc(z))
    fscale ;ST(1)=z, ST(0)=(2**trunc(z))*(2**(z-trunc(z)))=2**t
    fld qword [result]
    fmul

    fstp qword [rsp - 8]
    mov rdx, [rsp - 8]
    movq xmm0, rdx
    ret