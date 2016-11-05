#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/timer.h>
#include <linux/fs.h>
#define DELAY 3
#define TEXT "Hello, world!"

static unsigned long times = 0;
static unsigned char timer_exists = 0;

static int timer_init(void);
static void timer_exit(void);

static ssize_t times_show(struct kobject *, struct kobj_attribute *, char *);
static ssize_t times_store(struct kobject *, struct kobj_attribute *, const char *, size_t);

static void repeat(unsigned long);

