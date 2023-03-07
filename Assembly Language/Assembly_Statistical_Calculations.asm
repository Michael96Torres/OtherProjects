;  CS 218 - Assignment 9
;  Functions Template.

; --------------------------------------------------------------------
;  Write assembly language functions.

;  The value returning function, rdQuinaryNum(), should read
;  a quinary number from the user (STDIN) and perform
;  apprpriate error checking and conversion (string to integer).

;  The void function, countSort(), sorts the numbers into
;  ascending order (small to large).  Uses the insertion sort
;  algorithm modified to sort in ascending order.

;  The value returning function, lstAverage(), to return the
;  average of a list.

;  The void function, listStats(), finds the minimum, median,
;  and maximum, sum, and average for a list of numbers.
;  The median is determined after the list is sorted.
;  Must call the lstAverage() function.

;  The value returning function, coVariance(), computes the
;  co-variance for the two passed data sets.

;  The boolean function, rdQuinaryNum(), reads a quinary
;  number from standard input, performs conversion, and
;  error checks and range checks the value.

; ********************************************************************************

section	.data

; -----
;  Define standard constants.

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
SPACE		equ	" "
NULL		equ	0
ESC		equ	27

; -----
;  Define program specific constants.

MIN_NUM		equ	5
MAX_NUM		equ	156250
BUFFSIZE	equ	51			; 50 chars plus NULL

LIMIT		equ	MAX_NUM+1

; -----
;  NO static local variables allowed...


; ********************************************************************************

section	.text

; --------------------------------------------------------
;  Read an ASCII/quinary number from the user.
;  Perform appropriate error checking and, if OK,
;  convert to integer and return true.

;  If there is an error, print the applicable passed
;  error message string.

;  If the user enters a return (no other input, no
;  leading spaces), the function should return true.
;  This indicates no further input.

; -----
;  HLL Call:
;	status = rdQuinaryNum(&numberRead, promptStr, errMsg1,
;					errMsg2, errMSg3);

;  Arguments Passed:
;	1) numberRead, addr - rdi
;	2) promptStr, addr - rsi
;	3) errMsg1, addr - rdx
;	3) errMsg2, addr - rcx
;	3) errMsg3, addr - r8

;  Returns:
;	number read (via reference)
;	TRUE or FALSE


global	rdQuaternaryNum
rdQuaternaryNum:
	push rbp
	mov rbp, rsp
	sub rsp, 59
	push rbx
	push r12
	push r13
	push r14
	push r15
	
	mov r14, rdi
	mov r10, 0				;char count = 0
	lea rbx, byte[rbp-59]

	push rdi
	mov rdi, rsi
	call printString
	pop rdi
	
	
	getNxtChr:				;get character loop
	mov rax, SYS_read
	mov rdi, STDIN
	lea rsi, [rbp-9]
	mov rdx, 1
	syscall

	mov al, byte[rbp-9]			;read one chr
	cmp al, LF				;if ch==LF exit loop
	je inputDone

	mov byte[rbx], al
	cmp r10, 48				;if count>50 go to chr loop
	jge getNxtChr
	inc r10
	inc rbx					;i++
	jmp getNxtChr				;go to chr loop
;---------------------------------------------------------------
inputDone:							;exit chr loop
	mov byte[rbx],NULL				;add NULL

	cmp r10, 48				;if count>=50 get return status and exit
	jge over50Error
	cmp r10, 0				;if count=0 get return status and exit
	jne errorCheck

	mov rax, ENDOFINPUT			;equal zero return
	jmp endLp
over50Error:
	mov rax, INPUTOVERFLOW			;50 or over return
	jmp endLp
errorCheck:					;error check
	mov r10, 4
	lea rbx, byte[rbp-59]
firstFor:
	mov al, byte[rbx]			;mov character into al
	cmp al, SPACE
	jne secondFor
	inc rbx
	jmp firstFor
		;skip leading spaces
secondFor:
	cmp al, NULL
	je convert
	cmp al, "0"				;check remain for between "0" and "3"
	jl digitError
	cmp al, "3"
	jg digitError
	inc rbx
	mov al, byte[rbx]
	jmp secondFor

digitError:
							;if outside range return error
	mov rax, NOSUCCESS
	jmp endLp
;----------------------------------------------------------------
convert:						;convert
	mov r12, 4
	mov r11, 0					
	mov r13, 0					;runningSum = 0
	lea rbx, byte[rbp-59]
skipSpaceLp:					;skip spaces
	mov al, byte[rbx]			;get number from string
	cmp al, SPACE
	je wasSpace
	jmp q2intLoop
wasSpace:
	inc rbx
	jmp skipSpaceLp
q2intLoop:						;start convert Loop
	cmp al, NULL 
	je exitConvert
	sub al, "0"					;convert character to integer	
	mov r11b, al 
	mov rax, r13	 			;runningSum * 4 
	mul r12
	add rax, r11				;runningSum + digit
	mov r13, rax
	inc rbx						;inc address
	mov al, byte[rbx]
	jmp q2intLoop				;loop 
exitConvert:
mov rax, r13								
cmp rax, MAXNUM				;if num>max return max error
jg maxError
			;ret num via ref
mov dword[r14], eax						;get return success code
mov rax, SUCCESS
jmp endLp
maxError:

	mov rax, OVERMAX
	jmp endLp
	
endLp:
pop r15
pop r14
pop r13
pop r12
pop rbx
add rsp, 59
mov rsp, rbp
pop rbp
ret



; --------------------------------------------------------
;  Count sort function.

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


; -----
;  HLL Call:
;	call countSort(list, len)

;  Arguments Passed:
;	1) list, addr - rdi
;	2) length, value - rsi

;  Returns:
;	sorted list (list passed by reference)



global	countSort
countSort:

push rbp
mov rbp, rsp
sub rsp, 400000
push rax
push rbx
push rcx
push r12
push r13
push r14

;---------------------------------------
mov rbx, rbp
sub rbx, 400000
mov rcx, 100000
mov r12, 0
initializingLp:
mov dword[rbx+r12*4], 0       ;Zero Loop
inc r12
cmp r12, rcx
loop initializingLp
;---------------------------------------
;for i=o to (len-1)
;count[list[i]]=count[list[i]]+1

mov rax, 0
mov r12, 0
mov r10, 0

innerLp:
	mov eax, dword[rdi+r12*4]
	mov r10d, dword[rbx+rax*4]
	inc r10d
	mov dword[rbx+rax*4], r10d
	inc r12
	cmp r12, rsi               ;compare rcx, to length of array
	jne innerLp
	jmp outsideLoop
;-----------------------------------
outsideLoop:
;p=0
;for i=0 to(limit-1)
;if count[i] <> 0

mov r12, 99999
mov r10, 0
outerLp:
	cmp r12, 0
	jl finished
	mov eax, dword[rbx+r12*4]
	cmp eax, 0
	je increment
	jmp inLp
increment:
	dec r12
	jmp outerLp
;j=i to count[i]
;list[p]=1
;p=p+1
inLp:
	mov dword[rdi+r10*4], r12d
	dec eax
	inc r10
	cmp eax, 0
	je increment
	jmp inLp
finished:
pop r14
pop r13
pop r12
pop rcx
pop rbx
pop rax
mov rsp, rbp
pop rbp

ret



; --------------------------------------------------------
;  Find statistical information for a list of integers:
;	sum, average, minimum, median, and maximum

;  Note, for an odd number of items, the median value is defined as
;  the middle value.  For an even number of values, it is the integer
;  average of the two middle values.

;  This function must call the lstAvergae() function
;  to get the average.

;  Note, assumes the list is already sorted.

; -----
;  HLL Call:
;	call listStats(list, len, sum, ave, min, med, max)

;  Arguments Passed:
;	1) list, addr - rdi
;	2) length, value - rsi
;	6) sum, addr - rdx
;	7) ave, addr - rcx
;	3) minimum, addr - r8
;	4) median, addr - r9
;	5) maximum, addr - stack, rbp+16

;  Returns:
;	sum, average, minimum, median, and maximum
;		via pass-by-reference



;	YOUR CODE GOES HERE



; --------------------------------------------------------
;  Function to calculate the average of a list.
;  Note, must call the lstSum() function.

; -----
;  HLL Call:
;	ans = lstAverage(lst, len)

;  Arguments Passed:
;	1) list, address - rdi
;	2) length, value - rsi

;  Returns:
;	average (in eax)



;	YOUR CODE GOES HERE



; --------------------------------------------------------
;  Function to calculate the co-variance between two lists.
;  Note, the two data sets must be of equal size.

; -----
;  HLL Call:
;	coVariance(xList, yList, len)

;  Arguments Passed:
;	1) xList, address - rdi
;	2) yList, address - rsi
;	3) length, value - rdx

;  Returns:
;	covariance (in rax)



;	YOUR CODE GOES HERE




; ******************************************************************
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

; ******************************************************************
