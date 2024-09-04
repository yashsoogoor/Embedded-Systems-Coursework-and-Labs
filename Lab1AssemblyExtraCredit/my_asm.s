    AREA asm_func, CODE, READONLY
; Export my_asm function location so that C compiler can find it and link
    EXPORT my_asm
my_asm
;
; ARM Assembly language function to set LED1 bit to a value passed from C   
; LED1 gets value (passed from C compiler in R0)
; LED1 is on GPIO port 2 bit 5
; See Chapter 9 in the LPC1768 User Manual
; for all of the GPIO register info and addresses
; Pinnames.h has the mbed modules pin port and bit connections
;
; Load GPIO Port 2 base address in register R1 
    LDR     R1, =0x2009C040 ; 0x2009C040 = GPIO port 2 base address
; Move bit mask in register R2 for bit 5 only
    MOV.W   R2, #0x000020   ; 0x000020 = 1<<5 all "0"s with a "1" in bit 5
; value passed from C compiler code is in R0 - compare to a "0" 
    CMP     R0, #0          ; value == 0 ?
; (If-Then-Else) on next two instructions using equal cond from the zero flag
    ITE EQ
; STORE if EQ - clear led 1 port bit using GPIO FIOCLR register and mask
    STREQ   R2, [R1,#0x1C]  ; if==0, clear LED1 bit
; STORE if NE - set led 1 port bit using GPIO FIOSET register and mask
    STRNE   R2, [R1,#0x18]  ; if==1, set LED1 bit
; Return to C using link register (Branch indirect using LR - a return)
    BX      LR
    END