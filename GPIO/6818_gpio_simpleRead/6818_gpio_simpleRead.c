#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <asm/mach-types.h>
#include <linux/gpio.h>
#include <asm/gpio.h>
#include <asm/delay.h>
#include <linux/clk.h>
#include <mach/gpio.h>
#include <mach/soc.h>
#include <mach/platform.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define DRIVER_NAME "readgpio7"

#define GPIO7    (PAD_GPIO_E+1)

#define DEVICE_NAME  "readgpio7"


MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("TOPEET");


static int readgpio_init(void){
	int ret;
	printk(KERN_EMERG "init_readgpio\n");

	ret=gpio_request(GPIO7,DRIVER_NAME);
	if(ret){
		printk("request for gpio failed.\n");
		return ret;
	}
	else
		printk("GPIO request succeed.\n");
		
	ret=gpio_get_value(GPIO7);
	printk("GPIO7 is %d\n ",ret);
	return 0;
}
static void readgpio_exit(void){
	gpio_free(GPIO7);
	printk(KERN_EMERG "Unregiste readgpio7 \n");
	
}
module_init(readgpio_init);
module_exit(readgpio_exit);
