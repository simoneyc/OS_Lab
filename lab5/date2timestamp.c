#include<linux/module.h>

long long int ts;
int y = 1, m = 1, d = 1;

module_param(y, int, 0);
MODULE_PARM_DESC(y, "year");
module_param(m, int, 0);
MODULE_PARM_DESC(m, "month");
module_param(d, int, 0);
MODULE_PARM_DESC(d, "date");


int init_module(void) {
	int month_arr[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        int i, life_day = 0;

	if((y<1970) || (m<1) || (m>12) || (d<1) || (d>31)){
		printk(KERN_ERR "Invalid argument(s).\n");
		return -EINVAL;
	}

	for(i=0; i<(m-1); i++){
		life_day += month_arr[i];
		if(i==1 && (y%400==0 || (y%4==0 && y%100!=0))){
			life_day += 1;
		}
	}

        while(--y >= 1970){
		if(y%400==0 || (y%4==0 && y%100!=0))
			life_day += 366;
		else
			life_day += 365;
	}

	ts = (life_day + d -1)*86400;
        printk(KERN_INFO "date2timestamp insert successfully! ts=%lld\n",ts);

        return 0;
}

void cleanup_module(void) {
        printk(KERN_INFO "date2timestamp remove successffully!\n");
}

EXPORT_SYMBOL(ts);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("4110056030");
MODULE_DESCRIPTION("lab5");


