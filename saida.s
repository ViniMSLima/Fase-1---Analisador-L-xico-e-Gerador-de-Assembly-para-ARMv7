.text
.global _start

_start:

    @ --- Linha 0 ---
    LDR R0, =lit_10_0    @ Carrega o endereço da label
    VLDR.F64 D0, [R0]               @ Busca o valor double no endereço
    VPUSH {D0}
    VPOP {D0}            @ Tira da pilha para salvar
    VPUSH {D0}           @ DEVOLVE para a pilha (para o RES_HISTORY no final)
    LDR R0, =A
    VSTR.F64 D0, [R0]    @ Salva na variavel A
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #0]

    @ --- Linha 1 ---
    LDR R0, =lit_2_0    @ Carrega o endereço da label
    VLDR.F64 D0, [R0]               @ Busca o valor double no endereço
    VPUSH {D0}
    VPOP {D0}            @ Tira da pilha para salvar
    VPUSH {D0}           @ DEVOLVE para a pilha (para o RES_HISTORY no final)
    LDR R0, =B
    VSTR.F64 D0, [R0]    @ Salva na variavel B
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #8]

    @ --- Linha 2 ---
    LDR R0, =A
    VLDR.F64 D0, [R0]    @ Busca o valor de A
    VPUSH {D0}           @ Coloca na pilha para a conta
    LDR R0, =B
    VLDR.F64 D0, [R0]    @ Busca o valor de B
    VPUSH {D0}           @ Coloca na pilha para a conta
    VPOP {D1}    @ B
    VPOP {D0}    @ A
    VADD.F64 D2, D0, D1
    VPUSH {D2}
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #16]

    @ --- Linha 3 ---
    LDR R0, =lit_15_0    @ Carrega o endereço da label
    VLDR.F64 D0, [R0]               @ Busca o valor double no endereço
    VPUSH {D0}
    LDR R0, =lit_4_0    @ Carrega o endereço da label
    VLDR.F64 D0, [R0]               @ Busca o valor double no endereço
    VPUSH {D0}
    VPOP {D1}    @ B
    VPOP {D0}    @ A
    VDIV.F64 D2, D0, D1
    VCVT.S32.F64 S4, D2    @ Trunca as casas decimais
    VCVT.F64.S32 D2, S4    @ Converte de volta para Double
    VPUSH {D2}
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #24]

    @ --- Linha 4 ---
    LDR R0, =lit_15_0    @ Carrega o endereço da label
    VLDR.F64 D0, [R0]               @ Busca o valor double no endereço
    VPUSH {D0}
    LDR R0, =lit_4_0    @ Carrega o endereço da label
    VLDR.F64 D0, [R0]               @ Busca o valor double no endereço
    VPUSH {D0}
    VPOP {D1}    @ B
    VPOP {D0}    @ A
    VDIV.F64 D2, D0, D1    @ a / b
    VCVT.S32.F64 S4, D2    @ floor(a/b)
    VCVT.F64.S32 D2, S4    
    VMUL.F64 D2, D2, D1    @ (floor(a/b) * b)
    VSUB.F64 D2, D0, D2    @ a - (resultado acima)
    VPUSH {D2}
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #32]

    @ --- Linha 5 ---
    LDR R0, =lit_2_0    @ Carrega o endereço da label
    VLDR.F64 D0, [R0]               @ Busca o valor double no endereço
    VPUSH {D0}
    LDR R0, =lit_3_0    @ Carrega o endereço da label
    VLDR.F64 D0, [R0]               @ Busca o valor double no endereço
    VPUSH {D0}
    VPOP {D1}    @ B
    VPOP {D0}    @ A
    VMOV.F64 D2, #1.0      @ Acumulador da potencia
    VCVT.S32.F64 S4, D1    @ Converte expoente para int
    VMOV R1, S4            @ R1 = contador do loop
    CMP R1, #0
    BEQ pow_end_5_3
    pow_loop_5_3:
    VMUL.F64 D2, D2, D0    @ acc = acc * base
    SUBS R1, R1, #1        @ decrementa contador
    BNE pow_loop_5_3
    pow_end_5_3:
    VPUSH {D2}
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #40]

    @ --- Linha 6 ---
    LDR R0, =lit_0    @ Carrega o endereço da label
    VLDR.F64 D0, [R0]               @ Busca o valor double no endereço
    VPUSH {D0}
    VPOP {D0}            @ Indice do RES
    VCVT.S32.F64 S0, D0  @ Double para Int
    VMOV R1, S0
    LSL R1, R1, #3       @ Indice * 8 bytes
    LDR R0, =res_history
    VLDR.F64 D0, [R0, R1]
    VPUSH {D0}
    LDR R0, =lit_5    @ Carrega o endereço da label
    VLDR.F64 D0, [R0]               @ Busca o valor double no endereço
    VPUSH {D0}
    VPOP {D0}            @ Indice do RES
    VCVT.S32.F64 S0, D0  @ Double para Int
    VMOV R1, S0
    LSL R1, R1, #3       @ Indice * 8 bytes
    LDR R0, =res_history
    VLDR.F64 D0, [R0, R1]
    VPUSH {D0}
    VPOP {D1}    @ B
    VPOP {D0}    @ A
    VMUL.F64 D2, D0, D1
    VPUSH {D2}
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #48]

    @ --- Linha 7 ---
    LDR R0, =lit_50_0    @ Carrega o endereço da label
    VLDR.F64 D0, [R0]               @ Busca o valor double no endereço
    VPUSH {D0}
    VPOP {D0}            @ Tira da pilha para salvar
    VPUSH {D0}           @ DEVOLVE para a pilha (para o RES_HISTORY no final)
    LDR R0, =VALOR
    VSTR.F64 D0, [R0]    @ Salva na variavel VALOR
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #56]

    @ --- Linha 8 ---
    LDR R0, =VALOR
    VLDR.F64 D0, [R0]    @ Busca o valor de VALOR
    VPUSH {D0}           @ Coloca na pilha para a conta
    LDR R0, =lit_10_0    @ Carrega o endereço da label
    VLDR.F64 D0, [R0]               @ Busca o valor double no endereço
    VPUSH {D0}
    VPOP {D1}    @ B
    VPOP {D0}    @ A
    VDIV.F64 D2, D0, D1
    VPUSH {D2}
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #64]

    @ --- Linha 9 ---
    LDR R0, =lit_6    @ Carrega o endereço da label
    VLDR.F64 D0, [R0]               @ Busca o valor double no endereço
    VPUSH {D0}
    VPOP {D0}            @ Indice do RES
    VCVT.S32.F64 S0, D0  @ Double para Int
    VMOV R1, S0
    LSL R1, R1, #3       @ Indice * 8 bytes
    LDR R0, =res_history
    VLDR.F64 D0, [R0, R1]
    VPUSH {D0}
    LDR R0, =lit_8    @ Carrega o endereço da label
    VLDR.F64 D0, [R0]               @ Busca o valor double no endereço
    VPUSH {D0}
    VPOP {D0}            @ Indice do RES
    VCVT.S32.F64 S0, D0  @ Double para Int
    VMOV R1, S0
    LSL R1, R1, #3       @ Indice * 8 bytes
    LDR R0, =res_history
    VLDR.F64 D0, [R0, R1]
    VPUSH {D0}
    VPOP {D1}    @ B
    VPOP {D0}    @ A
    VADD.F64 D2, D0, D1
    VPUSH {D2}
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #72]

    MOV R7, #1
    SWI 0

.data
.align 3
res_history: .skip 80
A: .double 0.0
B: .double 0.0
VALOR: .double 0.0
@ Literais Numericos
lit_0: .double 0
lit_10_0: .double 10.0
lit_15_0: .double 15.0
lit_2_0: .double 2.0
lit_3_0: .double 3.0
lit_4_0: .double 4.0
lit_5: .double 5
lit_50_0: .double 50.0
lit_6: .double 6
lit_8: .double 8
