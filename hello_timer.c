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

static struct kobj_attribute times_attrb = __ATTR(interval, 0664, times_show, times_store);

static struct kobject *times_obj = NULL;

static struct timer_list timer;

static int __init timer_init() {

	init_timer_on_stack(&timer);

	times_obj = kobject_create_and_add("timer", NULL);
	if (!times_obj) {
		return -ENOMEM;
	}

	if (sysfs_create_file(times_obj, &times_attrb.attr)) {
		timer_exit();
		return -EINVAL;
	}

	return 0;
}
