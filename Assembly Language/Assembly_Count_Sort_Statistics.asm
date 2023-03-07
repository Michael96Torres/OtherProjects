; Michael Torres
; Section 1002
; Assignment #7

;  Sort a list of number using the count sort algorithm.
;  Also finds the minimum, median, maximum, sum, and average of the list.

; -----
;  Count Sort Algorithm:

;	for  i = 0 to (len-1)
;	    count[list[i]] = count[list[i]] + 1
;	endFor

;	p = 0
;	for  i = 0 to (limit-1) do
;	    if  count[i] <> 0  then
;		for  j = 1 to count[i]
;		    list[p] = i
;		    p = p + 1
;		endFor
;	    endIf
;	endFor

; **********************************************************************************
;  Macro, "int2quinary", to convert an unsigned base-10 integer value into
;  an ASCII string representing the quinary (base-5) value.
;  The incoming integer is an unsigned, doubleword value.

;  This macro stores the result into an ASCII string (byte-size, right justified,
;  blank filled, NULL terminated).
;  Assumes valid/correct data.  As such, no error checking is performed.

;  Example:  Since, 19 (base 10) is 34 (base-5), then the integer 19
;  would be converted to ASCII resulting in: "       34", NULL
;  (7 spaces, '3', '4' followed a NULL for a total of 10 bytes).

; -----
;  Arguments
;	%1 -> integer number (to be converted)
;	%2 -> string address (where to store resulting string)

%macro	int2quinary	2		;Second macro with 2 arguements

;Successive Division
	mov	eax, %1	;******
	mov 	rcx, 0			;digit counter starting at zero
	mov	ebx, 5			;Set this to divide by 5
%%divideLoop:
	mov	edx, 0
	div	ebx		;divides by 5   

	push	rdx		; push remainder on the stack
	inc 	rcx		; increase coutner

	cmp	eax,0		; if result greater than 0
	jne	%%divideLoop	; goes to loop


	;mov	rbx, num0String
	mov	r10, STR_LENGTH ;moving for number of spaces
	sub	r10, rcx	;subtracting by counter
	mov	rdi, 0		;moving 0 into rdi 

%%addSpace:
	mov byte[%2+rdi],32	;used to add spaces
	inc 	rdi
	dec	r10
	cmp	r10, 0		; controls when to stop adding blanks
	jne %%addSpace



%%popLoop:				; used to pop into string
	pop	rax
	add 	al, "0"			; adds a 0 into al
	mov	byte[%2+rdi], al	;+rdi
	inc	rdi
	;inc	rbx
	loop	%%popLoop
	mov	byte [%2+rdi], NULL  	; Null terminates the loop


%endmacro

;	YOUR CODE GOES HERE
;	PASTE "int2quinary" MACRO from Asst #6


; --------------------------------------------------------------
;  Simple macro to display a string to the console.
;	Call:	printString  <stringAddr>

;	Arguments:
;		%1 -> <stringAddr>, string address

;  Count characters (excluding NULL).
;  Display string starting at address <stringAddr>

%macro	printString	1
	push	rax					; save altered registers
	push	rdi					; not required, but
	push	rsi					; does not hurt.  :-)
	push	rdx
	push	rcx

	mov	rdx, 0
	mov	rdi, %1
%%countLoop:
	cmp	byte [rdi], NULL
	je	%%countLoopDone
	inc	rdi
	inc	rdx
	jmp	%%countLoop
%%countLoopDone:

	mov	rax, SYS_write				; system call for write (SYS_write)
	mov	rdi, STDOUT				; standard output
	mov	rsi, %1					; address of the string
	syscall						; call the kernel

	pop	rcx					; restore registers to original values
	pop	rdx
	pop	rsi
	pop	rdi
	pop	rax
%endmacro


; ---------------------------------------------

section	.data

; -----
;  Define constants.

TRUE		equ	1
FALSE		equ	0

EXIT_SUCCESS	equ	0			; Successful operation

STDIN		equ	0			; standard input
STDOUT		equ	1			; standard output
STDERR		equ	2			; standard error

SYS_read	equ	0			; system call code for read
SYS_write	equ	1			; system call code for write
SYS_open	equ	2			; system call code for file open
SYS_close	equ	3			; system call code for file close
SYS_fork	equ	57			; system call code for fork
SYS_exit	equ	60			; system call code for terminate
SYS_creat	equ	85			; system call code for file open/create
SYS_time	equ	201			; system call code for get time

LF		equ	10
NULL		equ	0
ESC		equ	27

LIMIT		equ	10000
STR_LENGTH	equ	12

; -----
;  Provided data

list	dd	  147,  1123,  2245,  4440,   165
	dd	   10,    54,    28,    13,   222
	dd	   69,   126,   571,   147,   228
	dd	   27,   120,   177,    75,    14
	dd	  181,    25,    15,    22,  1217
	dd	   10,    10,   129,   212,   134
	dd	  127,    64,   140,   172,    24
	dd	  125,    16,    62,     8,    92
	dd	 2161,   134,   151,    32,    12
	dd	   29,   114,    22,   113,  1131
	dd	 1113,  1232,  2146,  3376,  5120
	dd	 2356,  3164,  4565,  3155,  3157
	dd	 1001,   128,    33,   105,  8327
	dd	  101,   115,   108,  2233,  2115
	dd	 1227,  1226,  5129,   117,   107
	dd	  105,   109,   730,   150,  3414
	dd	 1107,  6103,  1245,  6440,   465
	dd	 2311,   254,  4528,   913,  6722
	dd	 1149,  2126,  5671,  4647,  4628
	dd	  327,  2390,   177,  8275,  5614
	dd	 3121,   415,   615,    22,  7217
	dd	   11,    10,   129,   812,  2134
	dd	 1221,    34,  6151,   432,   114
	dd	  629,   114,   522,  2413,   131
	dd	 5639,   126,    62,    41,   127
	dd	  877,   199,  5679,   101,  3414
	dd	  117,    54,    40,   172,  4524
	dd	  125,    16,  9762,    10,  3292
	dd	 2101,   133,   133,    50,  4532
	dd	 8619,    15,  1618,   113,   115
	dd	 1219,  3116,    62,    17,   127
	dd	 6787,  4569,    79,  5675,    14
	dd	 1104,  6825,    84,    43,    76
	dd	  134,  4626,   100,  4566,  2346
	dd	   14,  6786,   617,   183,  3512
	dd	 7881,  8320,  3467,  4559,  1190
	dd	  103,   112,   146,   186,   191
	dd	  186,   134,  1125,  5675,  3476
	dd	 2137,  2113,  1647,   114,    15
	dd	 6571,  7624,   128,   113,  3112
	dd	  724,  6316,    17,   183,  4352
	dd	 1121,   320,  4540,  5679,  1190
	dd	 9125,   116,   122,   117,   127
	dd	 5677,   101,  3727,   125,  3184
	dd	 1897,  6374,   190,    13,    24
	dd	  125,   116,  8126,  6784,  2329
	dd	 1104,   124,   112,   143,   176
	dd	 7534,  2126,  6112,   156,  1103
	dd	 6759,  6326,  2171,   147,  5628
	dd	 7527,  7569,  3177,  6785,  3514
	dd	  153,   172,  5146,   176,   170
	dd	 1156,   164,  4165,   155,  5156
	dd	  894,  6325,  2184,    43,    76
	dd	 5634,  7526,  3413,  7686,  7563
	dd	 2147,   113,   143,   140,   165
	dd	  191,   154,  2168,   143,   162
	dd	  511,  6383,   133,    50,   825
	dd	 5721,  5615,  4568,  7813,  1231
	dd	  169,   146,  1162,   147,   157
	dd	  167,   169,  2177,   175,  2144
	dd	 5527,  6364,   330,   172,    24
	dd	 7525,  5616,  5662,  6328,  2342
	dd	  181,   155,  2145,   132,   167
	dd	  185,   150,  5149,   182,   434
	dd	 6581,  3625,  6315,     9,   617
	dd	 7855,  6737,  6129,  4512,   134
	dd	  177,   164,  3160,   172,   184
	dd	  175,   166,  6762,   158,  4572
	dd	 6561,    83,  1133,   150,   135
	dd	 5631,  8185,  2178,   197,   185
	dd	  147,   123,  3645,    40,  1766
	dd	 3451,  1954,  4628,  1613,  5432
	dd	 5649,  6366,  2162,   167,   167
	dd	  177,   169,  2177,   175,   169
	dd	 1161,   122,  1151,    32,  8770
	dd	   29,  5464,  3242,  1213,   131
	dd	 5684,   179,  2117,   183,   190
	dd	  100,  4611,  3123,  3122,   131
	dd	 1123,  1142,  3146,    76,  5460
	dd	  156,  8964,  3466,   155,  4357
len	dd	400

min	dd	0
med	dd	0
max	dd	0
sum	dd	0
avg	dd	0

; -----
;  Misc. data definitions (if any).



; -----
;  Provided string definitions.

newLine		db	LF, NULL

hdr		db	"---------------------------"
		db	"---------------------------"
		db	LF, ESC, "[1m", "CS 218 - Assignment #7", ESC, "[0m"
		db	LF, "Count Sort", LF, LF, NULL

hdrMin		db	"Minimum:  ", NULL
hdrMax		db	"Maximum:  ", NULL
hdrMed		db	"Median:   ", NULL
hdrSum		db	"Sum:      ", NULL
hdrAve		db	"Average:  ", NULL

; ---------------------------------------------

section .bss

count		resd	LIMIT
tmpString	resb	STR_LENGTH

; ---------------------------------------------

section	.text
global	_start
_start:

; ******************************
;  Basic steps:
;	sort data
;	find statistical information


;	YOUR CODE GOES HERE

;Count Sort Algorithm:

;	for  i = 0 to (len-1)
;	    count[list[i]] = count[list[i]] + 1
;	endFor

;	p = 0
;	for  i = 0 to (limit-1) do
;	    if  count[i] <> 0  then
;		for  j = 1 to count[i]
;		    list[p] = i
;		    p = p + 1
;		endFor
;	    endIf
;	endFor

;initialize the counting loop
mov 	ecx, dword[len]			;setting ecx = to len
mov 	rsi, 0

initializeLoop:
	mov 	dword[count + rsi*4],0
	inc 	rsi 				; increases rsi counter
	loop 	initializeLoop 			; loops the loop

mov 	ecx,dword[len]				; moves the length into ecv
mov 	rsi, 0  				; resettting rsi into 0

countingLoop:
	mov 	eax, dword[list+rsi*4] 	; moving list into eax
	inc 	dword[count+rax *4] 	; increasing 
	inc 	rsi
	loop 	countingLoop			;loops the loop


mov r8d,0		;initializing values
mov esi, 0
mov rcx, LIMIT		;setting to limit
mov r10d, 0

lp1:
	cmp 	rsi, rcx			;cmp count to limit
	jge	turnFalse				; stop when equal to
	cmp 	dword[count + rsi *4],0 	;cmps the count to 0
	jne 	lp2				;if not equal goes to lp2
	inc	rsi				;inc count
	jmp 	lp1				;repeats loop

lp2:
	mov 	r9d, 1				; setting new count value
	cmp	r9d, dword[count+rsi*4]		; stops when bigger
	jg      lp1
	mov 	dword[list+r8d*4],esi		;moving esi into list
	dec	dword[count+rsi*4]		;decreasing count
	inc	r8d				;inc counter
	jmp	lp2

	
turnFalse:


mov	eax, dword[list]		;Placing first list value into min
mov	dword[min], eax			

mov	r8d, dword[len]			;last sorted list value into max
mov	eax, dword[list+r8d*4-4]
mov	dword[max], eax




mov	ecx,dword[len]			;initializing
mov	r8d, 0

sumloopy:				;loop to check sum
	cmp	r8d, ecx
	je	sumEnd			;check to see if count=len
	mov	eax, dword[list+r8d*4]	;mov it num into eax
	add 	dword[sum], eax		;adding that num
	inc	r8d			;inc count
	jmp	sumloopy

sumEnd:


;Calculate Average
mov	eax, dword[sum]			; places the sum into eax
mov	ebx, dword[len]			; plaecs length into ebx
mov	edx, 0				; clears edx
div 	ebx				; divides sum by lenght
mov	dword [avg],eax			; places value into ave

; Middle Valuee
; Is length even or odd?

mov	eax, dword[len]		;Used to set the values needed
mov 	edx,0
mov 	ebx, 2
div	ebx
cmp	edx, 0
je	evenMiddle2			; jumps to even middle if div by 2
; Add Middle
mov	ebx, dword[list+eax*4]	; moves it into ebx
mov	dword[med], ebx		; moves this into middle
jmp	middleDone2			; jumps to different loop


evenMiddle2:
	mov	ebx,dword[list + eax * 4] ;upper middle
	add 	ebx, dword[list + eax*4 - 4]  ;lower middle
	mov	eax,ebx
	mov	edx, 0
	mov	ebx, 2
	div 	ebx			; divides ebx
	mov	dword[med], eax	; moves the value into mid

middleDone2:




; ******************************
;  Display results to screen in vigesimal.

	printString	hdr

	printString	hdrMin
	int2quinary	dword [min], tmpString
	printString	tmpString
	printString	newLine

	
	printString	hdrMax
	int2quinary	dword [max], tmpString
	printString	tmpString
	printString	newLine

	printString	hdrMed
	int2quinary	dword [med], tmpString
	printString	tmpString
	printString	newLine

	printString	hdrSum
	int2quinary	dword [sum], tmpString
	printString	tmpString
	printString	newLine

	printString	hdrAve
	int2quinary	dword [avg], tmpString
	printString	tmpString
	printString	newLine
	printString	newLine

	

; ******************************
;  Done, terminate program.

last:
	mov	rax, SYS_exit
	mov	rbx, EXIT_SUCCESS
	syscall


