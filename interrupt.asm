global irq0HandlerStub
extern PitInterruptHandler

section .text
irq0HandlerStub:
    pusha                    
    call PitInterruptHandler 
    popa                     
    iret                     
