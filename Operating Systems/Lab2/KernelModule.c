#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/seq_file.h>
#include <asm/pgtable.h>
#include <asm/page.h>
#include <linux/pagemap.h>
#include <linux/pid.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/mm_types.h>
#include "linux/mm.h"

#define BUF_SIZE 1024
static int pid = 1;

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Khafizov_Bulat");
MODULE_DESCRIPTION("Lab2");
MODULE_VERSION("1.0");

static struct proc_dir_entry *parent;

static int      __init lab_driver_init(void);
static void     __exit lab_driver_exit(void);

static int      open_proc(struct inode *inode, struct file *file);
static int      release_proc(struct inode *inode, struct file *file);
static ssize_t  read_proc(struct file *filp, char __user *buffer, size_t length,loff_t * offset);
static ssize_t  write_proc(struct file *filp, const char __user *buff, size_t len, loff_t * off);

static struct file_operations proc_fops = {
	.open = open_proc,
	.read = read_proc,
	.write = write_proc,
	.release = release_proc
};

static size_t write_net_device_struct(char __user *ubuf) {
	char buf[BUF_SIZE];
	size_t len = 0;
	static struct net_device *dev;
	read_lock(&dev_base_lock);
	dev = first_net_device(&init_net);
	while (dev) {
		len += sprintf(buf + len, "found [%s]\n", dev->name);
		len += sprintf(buf + len, "base_address = %ld\n", dev->base_addr);
		len += sprintf(buf + len, "mem_start = %ld\n", dev->mem_start);
		len += sprintf(buf + len, "mem_end = %ld\n", dev->mem_end);
		dev = next_net_device(dev);
	}
	read_unlock(&dev_base_lock);
	if (copy_to_user(ubuf, buf, len)) {
		return -EFAULT;
	}
	return len;
}

static struct page *get_page_by_mm_and_address(struct mm_struct* mm, long address) {
	pgd_t *pgd;
	p4d_t *p4d;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;
    struct page *page = NULL;
    pgd = pgd_offset(mm, address);
    if (!pgd_present(*pgd)) {
        return NULL;
    }
    p4d = p4d_offset(pgd, address);
    if (!p4d_present(*p4d)) {
    	return NULL;
    }
    pud = pud_offset(p4d, address);
    if (!pud_present(*pud)) {
        return NULL;
    }
    pmd = pmd_offset(pud, address);
    if (!pmd_present(*pmd)) {
        return NULL;
    }
    pte = pte_offset_kernel(pmd, address);
    if (!pte_present(*pte)) {
        return NULL;
    }
    page = pte_page(*pte);
    return page;
}

static size_t write_page_information(char __user *ubuf, struct task_struct *task_struct_ref) {
	char buf[BUF_SIZE];
	int len = 0;
	struct page *page_struct;
	struct mm_struct *mm = task_struct_ref->mm;
	if (mm == NULL) {
		printk(KERN_INFO "Task_struct has no mm\n");
		return 0;
	}
	struct vm_area_struct *vm_current = mm->mmap;
	long start = vm_current->vm_start;
	long end = vm_current->vm_end;
	long address = start;
	while (address <= end) {
		page_struct = get_page_by_mm_and_address(mm, address);
		if (page_struct != NULL) {
			len += sprintf(buf + len, "flags = %d\n", page_struct->flags);
			len += sprintf(buf + len, "va = %x, pa= %x\n", address, page_struct->mapping);
			break;
		}
		address += PAGE_SIZE;
	}
	if (page_struct == NULL) {
		printk(KERN_INFO "Error getting page\n");
		return 0;
	}
	if (copy_to_user(ubuf, buf, len)) {
		return -EFAULT;
	}
	return len;
}

static ssize_t read_proc(struct file *filp, char __user *ubuf, size_t count, loff_t *ppos) {
	char buf[BUF_SIZE];
	int len = 0;
	struct task_struct *task_struct_ref = get_pid_task(find_get_pid(pid), PIDTYPE_PID);
	printk(KERN_INFO "Proc file read.....\n");
	if (*ppos > 0) {
		return 0;
	}
	if (task_struct_ref == NULL) {
		len += sprintf(buf, "Task_struct for process with PID %D is NULL. Can not get any information\n", pid);
		if (copy_to_user(ubuf, buf, len)) {
			return -EFAULT;
		}
		*ppos = len;
		return len;
	}
	len += write_net_device_struct(ubuf);
	len += write_page_information(ubuf, task_struct_ref);
	*ppos = len;
	return len;
}

static ssize_t write_proc(struct file *filp, const char __user *ubuf, size_t count, loff_t *ppos) {
	int num_of_read_digits, read_digit;
	char buf[BUF_SIZE];
	printk(KERN_INFO "Proc file was written.....\n");
	if (*ppos > 0 || count > BUF_SIZE){
        return -EFAULT;
    }
	if (copy_from_user(buf, ubuf, count)) {
		return -EFAULT;
	}
	num_of_read_digits = sscanf(buf, "%d", &read_digit);
	if (num_of_read_digits != 1) {
		return -EFAULT;
	}
	pid = read_digit;
	*ppos = strlen(buf);
	return strlen(buf);
}

static int open_proc(struct inode *inode, struct file *file) {
	printk(KERN_INFO "Proc file opened.....\n");
	return 0;
}

static int release_proc(struct inode *inode, struct file *file) {
	printk(KERN_INFO "Proc file released.....\n");
	return 0;
}

static int __init lab_driver_init(void) {
	parent = proc_mkdir("Lab2", NULL);
	if (parent == NULL) {
		pr_info("Error creating proc directory!");
		return -1;
	}
	proc_create("struct_info", 0666, parent, &proc_fops);
	pr_info("Device driver inserted.....");
	return 0;
}

static void __exit lab_driver_exit(void) {
	proc_remove(parent);
	pr_info("Device driver removed.....");
}

module_init(lab_driver_init);
module_exit(lab_driver_exit);