#include<linux/init.h>
#include<linux/module.h>
#include<linux/timekeeping.h>
#include<linux/time64.h>
#include<linux/rtc.h>
MODULE_LICENSE("Dual BSD/GPL");
static int hello_init(void)
{
 struct timespec64 time;
 struct rtc_time tm1;
 uint64_t local_time;
 ktime_get_real_ts64(&time);//get UTC time 
 local_time = (time.tv_sec - (sys_tz.tz_minuteswest * 60));//convert UTC time to local time
 rtc_time64_to_tm(local_time,&tm1);//store local time into a structure named tm1
 printk(KERN_ALERT"Hello, world\n");
 printk(KERN_ALERT "%02d:%02d:%02d\n",tm1.tm_hour+20,tm1.tm_min,tm1.tm_sec);
 return 0;
}
static void hello_exit(void)
{
 struct timespec64 time;
 struct rtc_time tm1;
 uint64_t local_time;
 ktime_get_real_ts64(&time);//get UTC time 
 local_time = (time.tv_sec - (sys_tz.tz_minuteswest * 60));//convert UTC time to local time
 rtc_time64_to_tm(local_time,&tm1);//store local time into a structure named tm1
 printk(KERN_ALERT"Goodbye, cruel world\n");
 printk(KERN_ALERT "%02d:%02d:%02d\n",tm1.tm_hour+20,tm1.tm_min,tm1.tm_sec);
}
module_init(hello_init);
module_exit(hello_exit);
