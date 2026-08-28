#include <stdint.h>

#define UART_OUTPORT 0x10000000

static void putc_sim(char c) {
  *((volatile uint32_t *)UART_OUTPORT) = (uint32_t)c;
}

static void puts_sim(const char *s) {
  while (*s) {
    putc_sim(*s++);
  }
}

static void puthex_sim(uint32_t val) {
  const char *hex_chars = "0123456789ABCDEF";
  puts_sim("0x");
  for (int i = 28; i >= 0; i -= 4) {
    putc_sim(hex_chars[(val >> i) & 0xF]);
  }
}
//Recursive integer print
static void putint_sim(uint32_t num) {
  if(num < 10)
    putc_sim('0'+num);
  else{
    putint_sim(num/10);
    putc_sim('0' + num % 10);
  }
}

int main(void) {
  puts_sim("\n====================================\n");
  puts_sim(" Keshav's Custom Firmware Running!\n");
  puts_sim("====================================\n");

  while (1) {
    puts_sim("Running main loop...\n");
    uint32_t a = 42;
    uint32_t b = 58;
    uint32_t sum = a + b;

    puts_sim("Result: ");
    puthex_sim(sum);
    puts_sim("\n");
    uint32_t x = 0;

    // Small delay loop (simulate some work)
     while(1){
        putint_sim(x * 1000);
        x++;
        puts_sim("\n");
      }
    }
  }
