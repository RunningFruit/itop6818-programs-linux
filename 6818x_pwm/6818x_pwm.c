#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/types.h>
#include <linux/io.h>
#include <linux/pwm.h>
#include <linux/fs.h>  
	
/*pwm for this buzzer*/
struct pwm_device *pwm = NULL;
    
    
static int __init buzzer_init(void)
{	
	int ret;
	printk(" check buzzer init.\n");

	pwm = pwm_request(2, "buzzer");
	if ( pwm == NULL ) {
		printk("buzzer open error.\n");
	}
	//printk(KERN_EMERG "pwm_request %d ",pwm);
	ret=pwm_config(pwm,100000,200000);
	printk("pwm_config %d ",ret);
	printk("pwm_config %d ",ret);
	ret=pwm_enable(pwm);
	printk("pwm_enable %d ",ret);
	
	printk(KERN_EMERG "done2.  \n") ;
	return 0;
}
    
static void __exit buzzer_exit(void)
{
	pwm_config(pwm,0,0);
	pwm_disable(pwm);               // 关闭pwm
	pwm_free(pwm);                  // 释放pwm
}
    
module_init(buzzer_init);
module_exit(buzzer_exit);

MODULE_DESCRIPTION("pwm_buzzer driver");
MODULE_LICENSE("GPL");
