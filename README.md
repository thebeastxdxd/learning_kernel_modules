# Writing basic Kernel modules
### following [tutorial](https://tldp.org/LDP/lkmpg/2.6/html/lkmpg.html#AEN121)

- to see all loaded kernel modules you can use `lsmod`
which just reads  from `/proc/modules`

- printk: logging mechanism for the kernel. has priority levels which need to be given.
for example: KERN_INFO (included from `linux/kernel.h`). To see the logging info you can use
`dmesg`, `/dev/kmsg`, or `/var/log/kernel.log`. make sure to change priority level, which can
be seen here `/proc/sys/kernel/printk`
- To compile a kernel module you need to use [kbuild](https://elixir.bootlin.com/linux/v2.6.36/source/Documentation/kbuild/modules.txt)
in the Makefile `obj-y` means to comiple into the kernel. While obj-m means to compile a module.
- compiling into the kernel is based on the configuration used when compiling the kernel. for example:
obj-$(CONFIG_FOO)

something you should consider doing is copying the config file to the headers.
usually the kernel config file is in `/boot`
```bash
cp /boot/config-`uname -r` /usr/src/linux-headers-`uname -r`/.config.
```

- you can look at the kernel symbols in `/proc/kallsyms`
