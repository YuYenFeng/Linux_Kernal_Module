#include<linux/init.h>
#include<linux/kernal.h>
#include<linux/module.h>
#include<linux/list.h>
#include<linux/slab.h>
#include<linux/types.h>
#include<linux/random.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("YuYen");

static LIST_HEAD(BMI_list);
struct BMI
{
	char name[3];
	int height;
	int weight;
	int bmi;
	char *type;
	struct list_head list;
};

int BMI_list_init(void)
{
	struct BMI *person;
	int h=0;
	int w=0;
	int bmi=0;
	int i=0;
	int j=0;
	int name_char=0;
	printk(KERN_INFO "Loading Module Success FengYuYen\n");
	for(i=0;i<5;i++)
	{
		person=kmalloc(sizeof(*person),GFP_KERNEL);
		for(j=0;j<3;j++)
		{	
			get_random_bytes(&name_char,sizeof(int)-1);
			name_char%=25;
			person->name[j]='a'+name_char;
		}
		get_random_bytes(&h,sizeof(int)-1);
		h%=200;
		while(h<150)
		{
			h=h%150+h;
		}
		get_random_bytes(&h,sizeof(int)-1);
		w%=100;
		while(h<45)
		{
			w=w%150+w;
		}
		bmi=(w*100000)/((h/10)*(h/10));
		person->height=h;
		person->weight=w;
		person->bmi=bmi;
		if(bmi<18500)
		{
			person->type="Toolight";
		}
		else if(bmi>=18500 && bmi<24000)
		{
			person->type="Normal";
		}
		else if(bmi>=24000 && bmi<27000)
		{
			person->type="Tooheavy";
		}
		else if(bmi>=27000)
		{
			person->type="Obesity";
		}
		INIT_LIST_HEAD(&person->list);
  		list_add_tail(&person->list,&BMI_list);
	}
	list_for_each_entry(person,&BMI,list,list)
 	{
  		printk(KERN_INFO "Name:%s Height:%d Weight:%d BMI:%d.%d Type:%s\n",
		person->name,person->height,person->weight,person->bmi/1000,person->bmi%1000,person->type);
 	}
 return 0;
}

void BMI_list_exit(void)
{
 struct BMI *person,*next;
 list_for_each_entry_safe(person,next,&BMI_list,list)
 {
  list_del(&person->list);
  kfree(person);
 }

 printk(KERN_INFO "Removing Module Success\n");
}

module_init(BMI_list_init);
module_exit(BMI_list_exit);