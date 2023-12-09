#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/types.h>

struct birthday {
int day;
int month;
int year;
struct list_head list;
};

struct birthday *ptr, *next;
int count=0;

static LIST_HEAD(birthday_list);

void add_node(int day, int month, int year){
	struct birthday *person;
	person = kmalloc(sizeof(struct birthday), GFP_KERNEL);
	person->day = day;
	person->month= month;
	person->year = year;
	list_add_tail(&person->list, &birthday_list);
}
	
/* This function is called when the module is loaded. */
int simple_init(void)
{
	printk(KERN_INFO "Loading Module\n");
	add_node(25,12,1977);
	add_node(26,12,1977);
	add_node(27,12,1977);
	add_node(28,12,1977);
	add_node(29,12,1977);
	list_for_each_entry(ptr, &birthday_list, list){
		printk(KERN_INFO "Day : %d, Month : %d, Year : %d\n", ptr->day, ptr->month, ptr->year);
	}
        return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	list_for_each_entry_safe(ptr, next, &birthday_list, list){
		list_del(&ptr->list);
		kfree(ptr);
	}
	count=0;
	list_for_each_entry(ptr, &birthday_list, list){
		count++;
	}
	printk(KERN_INFO "Number of elements remaining in the linked list : %d\n",count);
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
