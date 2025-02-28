global keyboardHandlerStub
extern keyboardInterruptHandler

section .text
keyboardHandlerStub:
    pusha                          ; save all registers
    call keyboardInterruptHandler  ; call the C handler
    popa                           ; restore all registers
    iret                           ; return from interrupt
