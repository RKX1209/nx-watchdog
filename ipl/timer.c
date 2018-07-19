#include <string.h>
#include "timer.h"
#include "heap.h"
#define WDT_TIMER_ID 4

unsigned long timeout = 10;
__attribute__((noreturn)) void timer_init(void) {
        /* Use WDT5 for watchdog timer */
        volatile watchdog_timers_t *wdt = GET_WDT(WDT_TIMER_ID);
        wdt->PATTERN = WDT_REBOOT_PATTERN;
        wdt->COMMAND = WDT_CMD_DISABLE_PATTERN;
        GET_WDT_REBOOT_CFG_REG(WDT_TIMER_ID) = 0xC0000000; // Hz
        // wdt->CONFIG = WDT_TIMER_ID |
	//       (timeout << WDT_CFG_PERIOD_SHIFT) |
	//       WDT_CFG_PMC2CAR_RST_EN;
        wdt->CONFIG = 0x8019;
        wdt->COMMAND = WDT_CMD_START_PATTERN;
        // while (1) {
        //
        // }
}
