[build-menu]
FT_01_LB=Build
FT_01_CM=gcc -g "%f" -o "%e"
FT_01_WD=
FT_00_LB=_Compile
FT_00_CM=gcc -g -c "%f"
FT_00_WD=

FT_02_LB=
FT_02_CM=
FT_02_WD=

[settings]
# per qualche motivo questo non funziona
comment_single=@

[indentation]
width=4
# 0 is spaces, 1 is tabs, 2 is tab & spaces
type=1


[keywords]
# all items must be in one line
instructions=add and asr b bic bl bx cmp eor ldmdb ldmfd ldr ldrb lsl lsr mls mov mul mvn orr pop ror rrx sdiv smull stmfd str strb sub svc tst udiv umull vadd vcvt vldr vmov vstr push beq bne bpl bhs blo bhi bge ble bgt blt ldreq ldrne streq strne strlt moveq movne movlt subne subeq sublt
registers=r0 r1 r2 r3 r4 r5 r6 r7 r8 r9 r10 r11 r12 r13 r14 r15 sp lr pc
directives=.text .data .global .byte .hword .word .string .code .if .else .endif .req .equ .section .type

