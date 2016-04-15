

.386
.model flat, stdcall
.stack 4096

main	PROTO C

.data

.code
asm_main	PROC C
	
	mov	eax, 0			;"score"
	INVOKE	main

asm_main	ENDP

asm_score	PROC C

	add		eax, 50
	mov		ecx, eax
	ret

asm_score	ENDP

end