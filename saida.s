.text
.global _start

_start:
    @ Inicializacao: Pilha e FPU
    LDR SP, =0x20000
    LDR R0, =(0xF << 20)
    MCR P15, 0, R0, C1, C0, 2
    ISB
    VMRS R0, FPEXC
    ORR  R0, R0, #0x40000000
    VMSR FPEXC, R0


    @ --- Linha 0 ---
    LDR R0, =lit_10_0
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    VPOP {D0}
    VPUSH {D0}
    LDR R0, =A
    VSTR.F64 D0, [R0]
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #0]

    @ --- Linha 1 ---
    LDR R0, =lit_20_0
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    VPOP {D0}
    VPUSH {D0}
    LDR R0, =B
    VSTR.F64 D0, [R0]
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #8]

    @ --- Linha 2 ---
    LDR R0, =A
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    LDR R0, =B
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    VPOP {D1}    @ B
    VPOP {D0}    @ A
    VADD.F64 D2, D0, D1
    VPUSH {D2}
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #16]

    @ --- Linha 3 ---
    LDR R0, =B
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    LDR R0, =A
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    VPOP {D1}    @ B
    VPOP {D0}    @ A
    VSUB.F64 D2, D0, D1
    VPUSH {D2}
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #24]

    @ --- Linha 4 ---
    LDR R0, =A
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    LDR R0, =B
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    VPOP {D1}    @ B
    VPOP {D0}    @ A
    VMUL.F64 D2, D0, D1
    VPUSH {D2}
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #32]

    @ --- Linha 5 ---
    LDR R0, =B
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    LDR R0, =A
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    VPOP {D1}    @ B
    VPOP {D0}    @ A
    VDIV.F64 D2, D0, D1
    VPUSH {D2}
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #40]

    @ --- Linha 6 ---
    LDR R0, =lit_2_0
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    LDR R0, =lit_3_0
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    VPOP {D1}    @ B
    VPOP {D0}    @ A
    LDR R0, =lit_1_0
    VLDR.F64 D2, [R0]
    MOV R1, #0
    LDR R0, =lit_0_0
    VLDR.F64 D4, [R0]
    LDR R0, =lit_1_0
    VLDR.F64 D5, [R0]
pow_l_6_3:
    VCMP.F64 D4, D1
    VMRS APSR_nzcv, FPSCR
    BGE pow_e_6_3
    VMUL.F64 D2, D2, D0
    VADD.F64 D4, D4, D5
    B pow_l_6_3
pow_e_6_3:
    VPUSH {D2}
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #48]

    @ --- Linha 7 ---
    LDR R0, =lit_15_0
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    LDR R0, =lit_4_0
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    VPOP {D1}    @ B
    VPOP {D0}    @ A
    VDIV.F64 D2, D0, D1      @ D2 = resultado real
    LDR R0, =lit_0_0
    VLDR.F64 D3, [R0]        @ Acumulador floor
    LDR R0, =lit_1_0
    VLDR.F64 D4, [R0]        @ Passo 1.0
    @ Loop de Truncamento manual
trunc_l_7_3:
    VADD.F64 D5, D3, D4
    VCMP.F64 D5, D2
    VMRS APSR_nzcv, FPSCR
    BGT trunc_e_7_3    @ Se passar do valor, para
    VMOV.F64 D3, D5
    B trunc_l_7_3
trunc_e_7_3:
    VMUL.F64 D3, D3, D1      @ floor * b
    VSUB.F64 D2, D0, D3      @ a - (floor * b)
    VPUSH {D2}
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #56]

    @ --- Linha 8 ---
    LDR R0, =lit_15_0
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    LDR R0, =lit_4_0
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    VPOP {D1}    @ B
    VPOP {D0}    @ A
    VDIV.F64 D2, D0, D1      @ D2 = resultado real
    LDR R0, =lit_0_0
    VLDR.F64 D3, [R0]        @ Acumulador floor
    LDR R0, =lit_1_0
    VLDR.F64 D4, [R0]        @ Passo 1.0
    @ Loop de Truncamento manual
trunc_l_8_3:
    VADD.F64 D5, D3, D4
    VCMP.F64 D5, D2
    VMRS APSR_nzcv, FPSCR
    BGT trunc_e_8_3    @ Se passar do valor, para
    VMOV.F64 D3, D5
    B trunc_l_8_3
trunc_e_8_3:
    VMOV.F64 D2, D3          @ D2 recebe o floor
    VPUSH {D2}
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #64]

    @ --- Linha 9 ---
    LDR R0, =lit_3
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    VPOP {D1}                @ N (relativo)
    LDR R0, =lit_0_0
    VLDR.F64 D0, [R0]        @ D0 = 0.0
    LDR R0, =lit_1_0
    VLDR.F64 D2, [R0]        @ D2 = 1.0
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VSUB.F64 D0, D0, D1
    MOV R1, #0               @ Contador inteiro
    LDR R0, =lit_0_0
    VLDR.F64 D6, [R0]        @ Contador float aux
    LDR R0, =lit_1_0
    VLDR.F64 D7, [R0]        @ Passo 1.0
res_l_9_3:
    VCMP.F64 D6, D0          @ Compara: contador >= indice?
    VMRS APSR_nzcv, FPSCR
    BGE res_e_9_3    @ Se ja chegou no indice, sai
    ADD R1, R1, #1           @ Incrementa R1 (inteiro)
    VADD.F64 D6, D6, D7      @ Incrementa D6 (float)
    B res_l_9_3
res_e_9_3:
    LSL R1, R1, #3           @ R1 = R1 * 8 bytes (Offset)
    LDR R0, =res_history     @ R0 = Endereco base do historico
    ADD R0, R0, R1           @ R0 = Base + Offset
    VLDR.F64 D0, [R0]        @ Busca o valor no endereco exato
    VPUSH {D0}
    LDR R0, =lit_7
    VLDR.F64 D0, [R0]
    VPUSH {D0}
    VPOP {D1}                @ N (relativo)
    LDR R0, =lit_0_0
    VLDR.F64 D0, [R0]        @ D0 = 0.0
    LDR R0, =lit_1_0
    VLDR.F64 D2, [R0]        @ D2 = 1.0
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VADD.F64 D0, D0, D2      @ Soma 1.0 para achar a linha atual
    VSUB.F64 D0, D0, D1
    MOV R1, #0               @ Contador inteiro
    LDR R0, =lit_0_0
    VLDR.F64 D6, [R0]        @ Contador float aux
    LDR R0, =lit_1_0
    VLDR.F64 D7, [R0]        @ Passo 1.0
res_l_9_7:
    VCMP.F64 D6, D0          @ Compara: contador >= indice?
    VMRS APSR_nzcv, FPSCR
    BGE res_e_9_7    @ Se ja chegou no indice, sai
    ADD R1, R1, #1           @ Incrementa R1 (inteiro)
    VADD.F64 D6, D6, D7      @ Incrementa D6 (float)
    B res_l_9_7
res_e_9_7:
    LSL R1, R1, #3           @ R1 = R1 * 8 bytes (Offset)
    LDR R0, =res_history     @ R0 = Endereco base do historico
    ADD R0, R0, R1           @ R0 = Base + Offset
    VLDR.F64 D0, [R0]        @ Busca o valor no endereco exato
    VPUSH {D0}
    VPOP {D1}    @ B
    VPOP {D0}    @ A
    VADD.F64 D2, D0, D1
    VPUSH {D2}
    VPOP {D0}
    LDR R0, =res_history
    VSTR.F64 D0, [R0, #72]

    B .

.data
.align 3
res_history: .skip 80
A: .double 0.0
B: .double 0.0

@ Pool de Literais
lit_0_0: .double 0.0
lit_1_0: .double 1.0
lit_10_0: .double 10.0
lit_15_0: .double 15.0
lit_2_0: .double 2.0
lit_20_0: .double 20.0
lit_3: .double 3
lit_3_0: .double 3.0
lit_4_0: .double 4.0
lit_7: .double 7
