

.386
.model flat, stdcall
.stack 4096

PlayGame	PROTO C

.data

.code
asm_main	PROC C
	
	mov	eax, 0			;"score"
	INVOKE	PlayGame

asm_main	ENDP

asm_score	PROC C	num:dword

	mov	eax, num
	add eax, 50
	ret

asm_score	ENDP

end