#include <stdint.h>

#include "loader.h"
#include "log.h"
#include "sbi.h"
#include "stdio.h"
#include "task.h"
#include "timer.h"
#include "trap.h"

extern uint8_t stext, etext;
extern uint8_t srodata, erodata;
extern uint8_t sdata, edata;
extern uint8_t sbss, ebss;
extern uint8_t boot_stack, boot_stack_top;

void clear_bss() {
  for (uint8_t *i = &sbss; i < &ebss; i++) {
    *i = 0;
  }
}

void main() {
  clear_bss();

  info("Hello, world!\n");

  mm_init();

  info("Back to world!\n");

  mm_remap_test();

  trap_init();

  trap_enable_timer_interrupt();

  timer_set_next_trigger();

  task_run_first_task();

  panic("Unreachable in main()!\n");
}
