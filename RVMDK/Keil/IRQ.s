;/*****************************************************************************/
;/* IRQ.S: IRQ Handler                                                        */
;/*****************************************************************************/
;/* This file is part of the uVision/ARM development tools.                   */
;/* Copyright (c) 2005-2006 Keil Software. All rights reserved.               */
;/* This software may only be used under the terms of a valid, current,       */
;/* end user licence from KEIL for a compatible version of KEIL software      */
;/* development tools. Nothing else gives you the right to use this software. */
;/*****************************************************************************/


; Vectored Interrupt Controller (VIC) definitions
VectorAddr      EQU    0xFFFFF030       ; VIC Vector Address Register
VectorAddrDaisy EQU    0xFC000030       ; Daisy VIC Vector Address Register


        AREA IRQ, CODE, READONLY 
        ARM

        PRESERVE8
        ALIGN
        EXPORT  IRQHandler

IRQHandler
        SUB     LR, LR, #4              ; Update Link Register
        STMFD   SP!, {R0-R12, LR}       ; Save Workspace & LR to Stack
        MRS     R0, SPSR                ; Copy SPSR to R0
        STMFD   SP!, {R0, R1}           ; Save SPSR to Stack (8-byte)
        LDR     R0, =VectorAddr        
        LDR     R0, [R0]                ; Read the Routine Address
        LDR     R1, =VectorAddrDaisy
        LDR     R1, [R1]  
        ; Padding between the acknowledge and re-enable of interrupts 
        ; For more details, please refer to the following URL 
        ; http://www.arm.com/support/faqip/3682.html 
        NOP
        NOP
        MSR     CPSR_c, #0x1F           ; Switch to SYS Mode and enable IRQ 
        STMFD   SP!, {R0, LR}           ; Save Link Register (8-byte Stack)
        LDR     LR, =IRQReturnAddress   ; Read the Return Address
        BX      R0                      ; Branch to the IRQ Handler
IRQReturnAddress
        LDMFD   SP!, {R0, LR}           ; Restore Link Register (8-byte Stack)
        MSR     CPSR_c, #0xD2           ; Switch to IRQ Mode
        LDR     R0, =VectorAddr         ; Write to the VectorAddress to clear 
        STR     R0, [R0]                ; the respective Interrupt
        LDR     R1, =VectorAddrDaisy    ; Write to the VectorAddressDaisy to
        STR     R1, [R1]                ; clear the respective Interrupt
        LDMFD   SP!, {R0, R1}           ; Restore SPSR to R0
        MSR     SPSR_cxsf, R0           ; Restore SPSR
        LDMFD   SP!, {R0-R12, PC}^      ; Return to program
         

        END
