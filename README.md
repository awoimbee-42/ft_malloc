# malloc

A homegrown version of malloc.

This is one of those projects that might seem fun,
but the restrictions from the subject make it terribly boring.

To inject this malloc in any program:

```bash
LD_PRELOAD=$PWD/libft_malloc.so ls -R /
```
