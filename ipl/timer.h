#define MAKE_REG32(a)   (*(volatile uint32_t *)(a))
#define TIMERS_BASE 0x60005000
#define MAKE_TIMERS_REG(n) MAKE_REG32(TIMERS_BASE + n)
#define TIMERUS_CNTR_1US_0 MAKE_REG32(TIMERS_BASE + 0x10)

typedef struct {
    uint32_t CONFIG;
    uint32_t STATUS;
    uint32_t COMMAND;
    uint32_t PATTERN;
} watchdog_timers_t;

#define GET_WDT(n) ((volatile watchdog_timers_t *)(TIMERS_BASE + 0x100 + 0x20 * n))
#define WDT_CFG				0x0
#define WDT_CFG_PERIOD_SHIFT		4
#define WDT_CFG_PERIOD_MASK		0xff
#define WDT_CFG_INT_EN			(1 << 12)
#define WDT_CFG_PMC2CAR_RST_EN		(1 << 15)
#define WDT_CMD_START_PATTERN		(1 << 0)
#define WDT_CMD_DISABLE_PATTERN		(1 << 1)
#define WDT_REBOOT_PATTERN 0xC45A
#define GET_WDT_REBOOT_CFG_REG(n) MAKE_REG32(TIMERS_BASE + 0x60 + 0x8*n)

void timer_init(void);
