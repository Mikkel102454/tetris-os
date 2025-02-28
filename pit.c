extern void irq0HandlerStub();
extern void keyboardHandlerStub();
extern void DrawPX(int x, int y, int color);
extern int MoveLeft();
extern int MoveRight();
extern void PushBlock();
extern void RotateBlock();
extern volatile int timedelay;
extern void startGame();
extern int GetInMenu();
extern volatile int inMainMenu;

static inline void SendByte(unsigned short port, unsigned char value);
static inline unsigned char ReadByte(unsigned short port);
void keyboardInterruptHandler();
void SetupPit();
// setup IDT
struct IdtEntry {
    unsigned short offsetLow;
    unsigned short selector;
    unsigned char zero;
    unsigned char typeAttr;
    unsigned short offsetHigh;
};

struct IdtPtr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

#define IDT_ENTRIES 256
#define IRQ0 32
#define IRQ1 33

#define PIT_CHANNEL0 0x40
#define PIT_COMMAND 0x43
#define PIT_FREQUENCY 1193182

#define KEYBOARD_DATA_PORT 0x60
#define PIC1_COMMAND 0x20 
#define KEYBOARD_BUFFER_SIZE 128

struct IdtEntry idt[IDT_ENTRIES];
struct IdtPtr idtPtr;

void LoadIdt() {
    asm volatile ("lidt (%0)" : : "r" (&idtPtr));
}

void SetIdtGate(int num, unsigned int base, unsigned short sel, unsigned char flags) {
    idt[num].offsetLow = base & 0xFFFF;
    idt[num].selector = sel;
    idt[num].zero = 0;
    idt[num].typeAttr = flags;
    idt[num].offsetHigh = (base >> 16) & 0xFFFF;
}

void InitIdt() {
    idtPtr.limit = sizeof(struct IdtEntry) * IDT_ENTRIES - 1;
    idtPtr.base = (unsigned int)&idt;
    LoadIdt();
}

typedef void (*isr_t)(void);
isr_t interruptHandlers[IDT_ENTRIES];

void RegisterInterruptHandler(int n, isr_t handler) {
    interruptHandlers[n] = handler;
}

void InitInterrupts() {
    SetIdtGate(IRQ0, (unsigned int)irq0HandlerStub, 0x08, 0x8E);
    SetIdtGate(IRQ1, (unsigned int)keyboardHandlerStub, 0x08, 0x8E);
}

void InitPic() {
    // initialize master and slave PIC
    SendByte(0x20, 0x11);
    SendByte(0xA0, 0x11);

    // remap IRQs 0-15 to IDT entries 32-47
    SendByte(0x21, 0x20);
    SendByte(0xA1, 0x28);
    
    // setup cascading
    SendByte(0x21, 0x04);
    SendByte(0xA1, 0x02);

    // set PICs to 8086 mode
    SendByte(0x21, 0x01);
    SendByte(0xA1, 0x01);

    SendByte(0x21, 0xFC);  
    SendByte(0xA1, 0xFF);  

    // unmask all IRQs
    SendByte(0x21, 0x00);
    SendByte(0xA1, 0x00);

    
}

volatile int tick = 0;

void SetPitFrequency(int frequency) {
    int divisor = PIT_FREQUENCY / frequency;

    SendByte(PIT_COMMAND, 0x36); 


    SendByte(PIT_CHANNEL0, divisor & 0xFF);      
    SendByte(PIT_CHANNEL0, (divisor >> 8) & 0xFF);  
}

void PitInterruptHandler() {
    tick++;
    SendByte(0x20, 0x20); 
}

void InitPit() {
    SetPitFrequency(100);
}

static inline void SendByte(unsigned short port, unsigned char value) {
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline unsigned char ReadByte(unsigned short port) {
    unsigned char value;
    asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

void SetupPit() {
    InitIdt();
    InitInterrupts();
    InitPic();
    InitPit();
    RegisterInterruptHandler(IRQ0, PitInterruptHandler);

    RegisterInterruptHandler(IRQ1, keyboardInterruptHandler);
    asm volatile("sti"); 
}



//keyboard

void keyboardInterruptHandler() {
    unsigned char scancode = ReadByte(KEYBOARD_DATA_PORT);

    if(GetInMenu() == 1){
        if(scancode == 0x1C){ // Enter
            inMainMenu = 0;
        }
    }else{
        if(scancode == 0x1E){ // A
            MoveLeft();
        } else if(scancode == 0x20){ // D
            MoveRight();
        }else if(scancode == 0x1F){ // S
            timedelay = 5;
        } else if(scancode == 0x9F){ // S Up
            timedelay = 100;
        } else if(scancode == 0x13){ // R
            RotateBlock();
        }
    }
    

    SendByte(PIC1_COMMAND, 0x20);
}



//music
void setup_dma(short channel, int address, short length);
void reset_dsp();
void generate_square_wave(char *buffer, int size, int frequency, int sample_rate);
void play_sound(char *buffer, int length);
void InitSount();
void WaitForDSPWrite();
// Definitions for ports and registers
#define DMA_CHANNEL 1
#define DMA_MASK 0x0A          // DMA Mask Register
#define DMA_FLIPFLOP 0x0C      // DMA Flip-Flop Reset Register
#define DMA_MODE 0x0B          // DMA Mode Register
#define DMA_ADDR 0x02          // DMA Address Register (Channel 1)
#define DMA_COUNT 0x03         // DMA Count Register (Channel 1)
#define DMA_PAGE 0x83          // DMA Page Register (Channel 1)

#define SB16_BASE 0x220        // Base address for Sound Blaster 16
#define DSP_RESET (SB16_BASE + 0x06)
#define DSP_WRITE (SB16_BASE + 0x0C)
#define DSP_READ (SB16_BASE + 0x0A)
#define DSP_STATUS (SB16_BASE + 0x0E)


// Setup DMA for Channel 1 (8-bit transfer)
void setup_dma(short channel, int address, short length) {
    // Extract parts of the address and length
    char page = (address >> 16) & 0xFF;
    char addr_low = address & 0xFF;
    char addr_high = (address >> 8) & 0xFF;
    char length_low = (length - 1) & 0xFF;
    char length_high = ((length - 1) >> 8) & 0xFF;

    // Disable the channel
    SendByte(DMA_MASK, 0x04 | channel);

    // Reset the flip-flop
    SendByte(DMA_FLIPFLOP, 0x00);

    // Set the transfer mode (single mode, read transfer)
    SendByte(DMA_MODE, 0x48 | channel);

    // Set the page number
    SendByte(DMA_PAGE, page);

    // Set the address
    SendByte(DMA_ADDR, addr_low);
    SendByte(DMA_ADDR, addr_high);

    // Set the transfer length
    SendByte(DMA_COUNT, length_low);
    SendByte(DMA_COUNT, length_high);

    // Enable the channel
    SendByte(DMA_MASK, channel);
}

// Reset the DSP
void reset_dsp() {
    SendByte(DSP_RESET, 1);    // Assert DSP reset
    for (volatile int i = 0; i < 10000; i++); // Small delay
    SendByte(DSP_RESET, 0);    // Deassert DSP reset

    // Wait for DSP to respond with 0xAA
    while (!(ReadByte(DSP_STATUS) & 0x80));
    if (ReadByte(DSP_READ) != 0xAA) {
        // Halt on error
        while (1);
    }
}
void WaitForDSPWrite() {
    while (!(ReadByte(DSP_STATUS) & 0x80)); // Wait for DSP write buffer to be ready
}
// Generate a simple square wave sound buffer
void generate_square_wave(char *buffer, int size, int frequency, int sample_rate) {
    int samples_per_cycle = sample_rate / frequency;
    for (int i = 0; i < size; i++) {
        buffer[i] = (i % samples_per_cycle < samples_per_cycle / 2) ? 0xFF : 0x00;
    }
}

// Play sound using the Sound Blaster DSP
void play_sound(char *buffer, int length) {
    reset_dsp();
    // Setup DMA for sound transfer
    WaitForDSPWrite();
    setup_dma(DMA_CHANNEL, (int)buffer, length);

    // Set DSP sampling rate
    SendByte(DSP_WRITE, 0x40);  // Set sampling rate command
    SendByte(DSP_WRITE, 0x1F);  // 8 kHz (0x1F)

    // Start playback
    SendByte(DSP_WRITE, 0x14);  // 8-bit single-cycle playback command
    SendByte(DSP_WRITE, (length - 1) & 0xFF);  // Length low byte
    SendByte(DSP_WRITE, (length - 1) >> 8);    // Length high byte

    // Wait for playback to complete
    for (volatile int i = 0; i < 1000000; i++);
}

void InitSount(){
    __attribute__((aligned(4096)))char sound_data[256];
    generate_square_wave(sound_data, 256,  1000, 10000); // Generate a 440 Hz tone

    play_sound(sound_data, 256); // Play the tone
}   