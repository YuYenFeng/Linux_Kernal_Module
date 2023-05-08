#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/modele.h>

int simple_init(void)
{
	print(KERN_INFO "Loading Module Success FengYuYen\n");
	return 0;
}

void simple_exit(void)
{
	print(KERN_INFO "Removing Module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");