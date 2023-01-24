#include <linux/init.h>
#include <linux/module.h>
#include <linux/timekeeping.h>
#include <linux/time64.h>
#include <linux/rtc.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#define BUF_LEN 80
MODULE_LICENSE("Dual BSD/GPL");
static int device_open; // 1 means that the device has been used.
static char msg[BUF_LEN]; // array msg is used to store time message.
static int open(struct inode *inode, struct file *file)
{
  struct timespec64 time;
  struct rtc_time tm1; 
  uint64_t local_time; 
  if(device_open) return -1; 
  device_open++; 
  ktime_get_real_ts64(&time);
  local_time = (time.tv_sec - (sys_tz.tz_minuteswest * 60));
  rtc_time64_to_tm(local_time,&tm1);
  sprintf(msg,"Hello world, the current time is %02d:%02d:%02d\n",(tm1.tm_hour+20)%24,tm1.tm_min,tm1.tm_sec);
  return 0; 
}//get current time 

static ssize_t read(struct file *filp, char *buffer,size_t length,loff_t *offset)
{ 
  if(*offset == BUF_LEN)
    return 0;
  if(BUF_LEN>length)
     return 0;
  if(copy_to_user(buffer,msg,BUF_LEN)!=0)
     return 0;
  *offset += BUF_LEN;
  return BUF_LEN; //if read successfully, return the msg length
}

static int release(struct inode *inode, struct file *file)
{
   device_open--; 
   return 0;
}
static struct file_operations my_fops = 
{
 .open = open,
 .release = release,
 .read = read
};//define the instruction set

static struct miscdevice my_dev = 
{
  .minor = MISC_DYNAMIC_MINOR,
  .name = "lab4",
  .fops = &my_fops
};//define miscdevice struct 


static int install_module(void)
{
  misc_register(&my_dev);
  return 0;
}

static void uninstall_module(void)
{
   misc_deregister(&my_dev);
}

module_init(install_module);
module_exit(uninstall_module);
  









