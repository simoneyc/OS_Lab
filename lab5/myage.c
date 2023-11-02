#include<linux/module.h>
#include<linux/time.h>

extern long long int ts;

int init_module(void) {
	int leap_year[13] = {0};
	int yy=0;
	int age = 0, day = 0, total_days = 0, i, j = 0, count = 0;
	long long int x=0;
	long long int now = ktime_get_real_seconds();
	for(yy=0; yy<13 ;yy++){
		leap_year[yy] = 1972+4*yy;
	}

	printk(KERN_INFO "myage insert successfully!\n");
	if(now < ts)
		printk(KERN_INFO "Am I a joke(? :)\n");
	else{
		x = now - ts;
		age = x/(86400*365);
		for(i=2022; ((i>0) && (count<age)); i--) {
			if(i == leap_year[j]){
				total_days += 366;
			        j++;
			}
			else{
				total_days += 365;	
			}
			count ++;
		}

		day = ((x/86400) - total_days);
		printk(KERN_INFO "Wow you have survived on this world %d years and %d days!\n", age, day);
	}

	return 0;
}

void cleanup_module(void) {
        printk(KERN_INFO "myage remove successffully!\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("4110056030");
MODULE_DESCRIPTION("lab5");
