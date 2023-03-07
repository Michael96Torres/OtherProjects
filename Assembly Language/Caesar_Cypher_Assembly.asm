;Michael Torres
;Section 1002
;Assignment 11A

;  CS 218 - Assignment #11
;  Functions Template

; ***********************************************************************
;  Data declarations
;	Note, the error message strings should NOT be changed.
;	All other variables may changed or ignored...

section	.data

; -----
;  Define standard constants.

TRUE		equ	1
FALSE		equ	0

SUCCESS		equ	0			; successful operation
NOSUCCESS	equ	1			; unsuccessful operation

STDIN		equ	0			; standard input
STDOUT		equ	1			; standard output
STDERR		equ	2			; standard error

SYS_read	equ	0			; system call code for read
SYS_write	equ	1			; system call code for write
SYS_open	equ	2			; system call code for file open
SYS_close	equ	3			; system call code for file close
SYS_lseek	equ	8			; system call code for file repositioning
SYS_fork	equ	57			; system call code for fork
SYS_exit	equ	60			; system call code for terminate
SYS_creat	equ	85			; system call code for file open/create
SYS_time	equ	201			; system call code for get time

LF		equ	10
SPACE		equ	" "
NULL		equ	0
ESC		equ	27

O_CREAT		equ	0x40
O_TRUNC		equ	0x200
O_APPEND	equ	0x400

O_RDONLY	equ	000000q			; file permission - read only
O_WRONLY	equ	000001q			; file permission - write only
O_RDWR		equ	000002q			; file permission - read and write

S_IRUSR		equ	00400q
S_IWUSR		equ	00200q
S_IXUSR		equ	00100q

; -----
;  Define program specific constants.

BUFF_SIZE	equ	750000			; buffer size

; -----
;  Variables for getFileDescriptors() function.

usageMsg	db	"Usage: ./cracker -i <inputFileName> "
		db	"-o <outputFileName>", LF, NULL
errIncomplete	db	"Error, incomplete command line arguments.", LF, NULL
errExtra	db	"Error, too many command line arguments.", LF, NULL
errInputSpec	db	"Error, invalid input file specifier.", LF, NULL
errOutputSpec	db	"Error, invalid output specifier.", LF, NULL
errInputFile	db	"Error, unable to open input file.", LF, NULL
errOutputFile	db	"Error, unable to open output file.", LF, NULL

; -----
;  Variables for getCharacter() function.

wasEOF      db FALSE
atEOF       db FALSE
bufferMax   dq BUFF_SIZE
curr        dq BUFF_SIZE
buffMax     dq BUFF_SIZE

currIdx     dq BUFF_SIZE


errRead		db	"Error, reading input file.", LF,
		db	"Program terminated.", LF, NULL

; -----
;  Variables for putCharacter() function.

errWrite	db	"Error, writting to output file.", LF,
		db	"Program terminated.", LF, NULL

; -----
;  Variables for cracker() function.

rotate		dd	0
diff		dd	0.0
min		dd	27.0
total		dq	0.0
tmpKey     dq  0.0
tmp        dd  0.0
leastSquares    dd  0.0

zero    dq  0.0
len     dq 0.0

found	dd	0.0, 0.0, 0.0, 0.0, 0.0
		dd	0.0, 0.0, 0.0, 0.0, 0.0
		dd	0.0, 0.0, 0.0, 0.0, 0.0
		dd	0.0, 0.0, 0.0, 0.0, 0.0
		dd	0.0, 0.0, 0.0, 0.0, 0.0
		dd	0.0

freq	dd	0.07833		; a
		dd	0.01601		; b
		dd	0.02398		; c
		dd	0.04554		; d
		dd	0.12706		; e
		dd	0.02039		; f
		dd	0.02352		; g
		dd	0.05742		; h
		dd	0.06827		; i
		dd	0.00250		; j
		dd	0.01107		; k
		dd	0.03974		; l
		dd	0.02605		; m
		dd	0.06622		; n
		dd	0.07617		; o
		dd	0.01904		; p
		dd	0.00070		; q
		dd	0.05445		; r
		dd	0.06205		; s
		dd	0.09500		; t
		dd	0.02997		; u
		dd	0.00849		; v
		dd	0.02563		; w
		dd	0.00195		; x
		dd	0.01964		; y
		dd	0.00080		; z


; -----
;  Variables for decrypt() function.
;	this should not happen and was included only
;	for debugging purposes.

badErr		db	"Error, can not write null.", LF, NULL

fileDescription     dq  0


; ------------------------------------------------------------------------
;  Unitialized data

section	.bss

buffer		resb	BUFF_SIZE


; ############################################################################

section	.text

; ***************************************************************
;  Routine to get file descriptors.
;	Must parse command line arguments, check for errors,
;	attempt to open file, and, if files open
;	successfully, return descriptors (via reference)
;	and return TRUE.
;	Otherwise, display appropriate error message and
;	return FALSE.

;  Command Line format:
;	./cracker -i <inputFileName> -o <outputFileName>

; -----
;  HLL Call:
;	getFileDescriptors(argc, argv, &readFile, &writeFile)

; -----
;  Arguments:
;	argc, value
;	argv table, address
;	input file descriptor, address
;	output file descriptor, address
;  Returns:
;	file decriptors, via reference
;	TRUE (if worked) or FALSE (if error)


;	YOUR CODE GOES HERE
global getFileDescriptors
getFileDescriptors:

    push rbp 
    push rbx 
    push r12
    push r13
    push r14
    push r15

    mov r12, rdi
    mov r13, rsi
    mov r14, rdx
    mov r15, rcx

    
    cmp r12, 1
    jne checkingArgs
    ;If no args it will output error
    mov rdi, usageMsg
    call printString    ;outputs error
    mov rax, FALSE
    jmp getFileDone

;CHECKING THE ARGUMENTS
checkingArgs:
    cmp r12, 5
    je inputSpec
    cmp r12, 5
    jb tooLittleArgs
    cmp r12, 5
    ja tooManyArgs

;ERROR CODE TOO MANY ARGS
tooLittleArgs:
    mov rdi, errIncomplete
    call printString
    mov rax, FALSE
    jmp getFileDone

;ERROR CODE TOO MANY ARGS
tooManyArgs:
    mov rdi, errExtra
    call printString
    mov rax, FALSE
    jmp getFileDone

;CHECKING INPUT SPEC
inputSpec:
    mov rbx, qword[r13+8]

    cmp byte[rbx], '-'
    jne errorInputSpec

    cmp byte[rbx+1], 'i'
    jne errorInputSpec

    cmp byte[rbx+2], NULL
    jne errorInputSpec

    jmp checkInput

;ERROR CODE: INPUT SPEC
errorInputSpec:
    mov rdi, errInputSpec
    call printString
    mov rax, FALSE
    jmp getFileDone

;Checks the input file
checkInput:
    mov rax, SYS_open
    mov rdi, qword[r13+16]
    mov rsi, O_RDONLY
    syscall

    cmp rax, 0              ;if negative, error
    jl errorInputFile

    mov qword[r14], rax     ;moving file desc into
    jmp outputSpec


errorInputFile:
    mov rdi, errInputFile
    call printString
    mov rax, FALSE
    jmp getFileDone

;Checks output Spec
outputSpec:
    mov rbx, qword[r13+24]
    cmp byte[rbx], '-'
    jne errorOutputSpec

    cmp byte[rbx+1], 'o'    
    jne errorOutputSpec

    cmp byte[rbx+2], NULL
    jne errorOutputSpec

    jmp checkOutFile

;ERROR CODE: OUTPUT SPEC
errorOutputSpec:
    mov rdi, errOutputSpec
    call printString
    mov rax, FALSE
    jmp getFileDone


;CHECKING OUTPUT FILE
checkOutFile:
    mov rax, SYS_creat
    mov rdi, qword[r13+32]
    mov rsi, S_IRUSR | S_IWUSR
    syscall

    cmp rax, 0
    jl errorOutputFile

    mov qword[r15], rax
    jmp setTrue

;ERROR CODE OUTPUT FILE
errorOutputFile:
    mov rdi, errOutputFile
    call printString
    mov rax, FALSE
    jmp getFileDone

setTrue:            ;used to set func to true and end
    mov rax, TRUE   

getFileDone:

    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp


ret



; ***************************************************************
;  Get character routine
;	Returns one character.
;	If buffer is empty, fills buffer.
;	This routine performs all buffer management.

;	The read buffer itself and some misc. variables are
;	used ONLY by this routine and as such are not passed.

; ----
;  HLL Call:
;	status = getCharacter(readFileDesc, &char);

;  Arguments:
;	input file descriptor, value
;	character, address
;  Returns:
;	status (SUCCESS or NOSUCCESS)
;	character, via reference



;	YOUR CODE GOES HERE


global getCharacter
getCharacter:

	push rbp
	push rbx
	push r12
    push r13
    push r14
    push r15

	mov r12, rdi    ;file desc
	mov r13, rsi    ;Char address
	mov r14, qword[curr]     ;placing idx into r14


    cmp r14, qword[bufferMax]     ;Index>=bufferMax
    jb checkDone


        cmp byte[wasEOF], TRUE      ;Goes until True
        jne readingFile
        mov rax, FALSE              ;If False ends func
        jmp getCharDone                    ;jumps to exit

    ;Where reading occur
    readingFile:
        mov rax, SYS_read      
        mov rdi, r12
        mov rsi, buffer
        mov rdx, BUFF_SIZE
        syscall


        cmp rax, 0      ;if bad read
        jl errorRead   ; jmps to read

    ;rd<=requested
    checkingRead:           ;Reac check
        cmp rax,rdx
        jae changeCurr      ;change the current index
        mov qword[bufferMax], rax
        mov byte[wasEOF], TRUE

    changeCurr:
        mov r14,0
        mov qword[curr], r14    ;sets the curr index to 0
        jmp checkDone           ; checks done
    
    ;ERROR CODE: bad read
    errorRead:
        mov rdi, errRead
        call printString
        mov rax, FALSE
        jmp getCharDone

;Checks if done and end function
    checkDone:
        mov rsi, buffer     ;places the buffer into rsi
        mov r15, 0
        mov r15b, byte[rsi+r14] ;setting to currIdx
        mov byte[r13], r15b     ;returning the read

        inc r14
        mov qword[curr], r14
        mov rax, TRUE
        ;Set to true and end func

getCharDone:
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp
ret



; ***************************************************************
;  Write character to output file.
; -----
;  HLL Call:
;	status = putCharacter(writeFileDesc, char);

;  Arguments are:
;	write file descriptor (value)
;	character (value)
;  Returns:
;	SUCCESS or NOSUCESS

; -----
;  This routine returns SUCCESS when character has been written
;	and returns NOSUCCESS only if there is an
;	error on write (which would not normally occur).


global putCharacter
putCharacter:
    push rbp
    push rbx
    push r12
    push r13

    ;getting desc value
    mov r12, rdi
    ;Getting Char Value
    mov byte[r13],sil

    mov rax, SYS_write
    mov rdi, r12    ;file desc
    mov rsi, r13    ;Chars Address
    mov rdx, 1      ;written at a time
    syscall

    cmp rax, 0
    jl errorWrite

    mov rax, TRUE       ;moving true into rax, ending func
    jmp putCharacterDone

;ERROR CODE: Writing Error
errorWrite:
    mov rdi, errWrite
    call printString
    mov rax, FALSE

;Exiting the Funcrion
putCharacterDone:
    pop r13
    pop r12
    pop rbx
    pop rbp

ret


; ***************************************************************
;  CS 218 - Ceasar Cypher Decryption Routine.

;  Ceasar Cyphers can be automatically broken by taking
;	advantage of the known letter frequencies for the
;	English language.

;  The frequencies found in the encrypted text are
;	compared against the known frequencies table.  This
;	requires comparing two lists, which is done using the
;	sum of the squares of the differences of the corresponding
;	entries in the list.  By minimizing this sum, you find
;	the best match.  This is called the "least squares fit".
;	As such, based on the letter frequencies, the routine
;	will find the appropriate decryption rotation key.

;  Note, this routine accepts as input the address a "count"
;	array.  The array must have 26 elements, with the first
;	element, or count(0)  being the number of A's, and count(1)
;	being the number of B's found in the original encrypted text.

; -----
;  HLL call:
;	key = cracker(ltrCounts);

; -----
;  Arguments passed
;	populated letter count array, address
;  Returns:
;	rotation key


;	YOUR CODE GOES HERE

global cracker
cracker:

    push rbp            ;prologue
    push rbx
    push r12
    push r13
    push r14
    push r15

    mov r12, rdi 
    mov rbx,0               ;used to go through letters
    
    mov rcx, 26
    mov r13d, dword[total]
    


    getLetters:
        add r13d, dword[r12+rbx*4]      ;gets letters
        inc rbx
        loop getLetters
    mov dword[total],r13d               ;storing them in var

    mov rcx, 26
    mov rbx,0
    

    freqPlacement:       ;places found freq into array
        mov r14,0
        mov r14d, dword[r12+rbx*4]
        cvtsi2ss xmm0, r14
        cvtsi2ss xmm1, r13      ;the total
        divss xmm0,xmm1         
        ;divide count by the total
        movss dword[found+rbx*4], xmm0   ;storing found
        inc rbx
        loop freqPlacement

mov r15d, dword[rotate]     ;this is the key

leastSquare:
    mov rbx,0
    movsd xmm4, qword[zero]     ;initialization

    innerLoop:                  ;conducting formula one at a time
        mov rax, rbx            
        add rax, r15            ;change index by rotation
        mov rdx, 0
        mov r8, 26              ;div bt 26
        div r8

        mov rax, rbx
        movss xmm2, dword[found+rdx*4]      ;known freq
        movss xmm3, dword[freq+rbx*4]       ;found frew
        subss xmm3, xmm2                ;known-found freq
        mulss xmm3, xmm3                ;squaring value
        addss xmm4, xmm3                ;Summation
        inc rbx                         ;next value
        cmp rbx, 26                     ;Goes until last letter
        jb innerLoop

    ucomiss xmm4, dword[min]            ;compare sum to min
    jae nextTest                        ;if larger skip to next
    movss dword[min], xmm4              ;store new least square
    mov dword[rotate],r15d

    nextTest:               ;goes onto next square
        inc r15
        cmp r15, 26
        jb leastSquare

        mov eax, dword[rotate]
 
    crackerDone:     

    pop r15         ;epilogue
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp
ret


; ***************************************************************
;  Decrypt the characters in the file.

;  Basic loop will:
;	get a character from input file (get_chr)
;	if letter, decrypt character (i.e., subtract key)
;	write decrypted character to output file

;  HLL Call:
;	status = decrypt(key, readFile, writeFile);

; -----
;  Arguments:
;	key, value
;	input file descriptor, value
;	output file descriptor, value


;	YOUR CODE GOES HERE


global decryptChar
decryptChar:

    cmp rsi, 64     ;correspomngs to ascii value before "A"
    ja upperCase

    jmp notLetter

    ;if letter is upperCase
    upperCase:
        cmp rsi, 91     ;corresponds to ascii value after "Z"
        jb uppperCont

        cmp rsi, 96     ;corresponds to ascii value before "a"
        ja lowerCase
    
        jmp notLetter

    ;if letter is lowercase
    lowerCase:
        cmp rsi, 123    ;correspods to ascii value after "z"
        jb lowerCont

    notLetter:
        mov rax, rsi
    ret
    uppperCont:
        mov r11d, 26
        mov r12d, r11d
        sub r12d, edi

        sub esi, 65     ;Ascii "A" value

        mov eax, r12d
        add eax, esi
        mov edx,0
        div r11d
        mov eax,65      ;Ascii "A" value
        add eax, edx

        ret
        

    lowerCont:
        mov r11d, 26
        mov r12d, r11d
        sub r12d, edi

        sub esi, 97             ;Asci "a" value

        mov eax, r12d
        add eax, esi
        mov edx,0
        div r11d
        mov eax,97
        add eax, edx

    ret

; ***************************************************************
;  Reset read file to beginning.
;	note, must also re-set some buffer variables
;	(variable names will vary).

; -----
;  Arguments
;	input file descriptor

;  Return
;	nothing
;	but, file is reset to beginning

global	resetRead
resetRead:


    mov qword[curr], BUFF_SIZE
    mov qword[bufferMax], BUFF_SIZE
    mov byte[wasEOF], FALSE

	mov	rax, SYS_lseek
	mov	rdi, rdi
	mov	rsi, 0
	mov	rdx, 0
	syscall

	ret

; ***************************************************************
;  Generic procedure to display a string to the screen.
;  String must be NULL terminated.

;  Algorithm:
;	Count characters in string (excluding NULL)
;	Use syscall to output characters

; -----
;  HLL Call:
;	printString(stringAddr);

;  Arguments:
;	1) address, string
;  Returns:
;	nothing

global	printString
printString:

; -----
;  Count characters to write.

	mov	rdx, 0
strCountLoop:
	cmp	byte [rdi+rdx], NULL
	je	strCountLoopDone
	inc	rdx
	jmp	strCountLoop
strCountLoopDone:
	cmp	rdx, 0
	je	printStringDone

; -----
;  Call OS to output string.

	mov	rax, SYS_write			; system code for write()
	mov	rsi, rdi			; address of char to write
	mov	rdi, STDOUT			; file descriptor for std in
						; rdx=count to write, set above
	syscall					; system call

; -----
;  String printed, return to calling routine.

printStringDone:
	ret

; ***************************************************************
