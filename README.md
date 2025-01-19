A Data Structure occupies specific addresses in RAM. We ask OS to allocate some memory for us to store the **value**, and it gives us specific **addresses**. For example, if we run the C++ code:

```C++
#include <iostream>

int main() {
	int p[3] = {1, 2, 3};
	for (int i = 0; i < 3; i++) {
		std::cout << "Address of p[" << i << "] = " << &p[i] << std::endl;
	}
	std::cout << "Address of (p[0] + 1) = " << (&p[0] + 1) << std::endl;
	std::cout << "Value of (p[0] + 1) = " << *(&p[0] + 1) << std::endl;
	return 0;
}
```

The result of the execution look like this:

```text
Address of p[0] = 0x16dcb3188
Address of p[1] = 0x16dcb318c
Address of p[2] = 0x16dcb3190
```

We can now copy-pasting these values into Python interpreter and confirm that indeed - every integer pointer has exactly 4 addresses (default clang value on Apple Silicon) to store its value:

```text
In [1]: p0_addr = 0x16dcb3188
In [2]: p1_addr = 0x16dcb3188
In [3]: p2_addr = 0x16dcb3190
In [4]: p1_addr - p0_addr
Out[4]: 4
In [5]: p2_addr - p1_addr
Out[5]: 4
```

When you increment or decrement a pointer, it moves by the size of the type it points to:

```text
Address of (p[0] + 1) = 0x16f00717c
Value of (p[0] + 1) = 2
```

But how can we check at what stage does OS allocate memory? We can use `strace`. It allows to monitor the system calls made by a program and the signals it receives.

```shell
strace ./memory_demo
```

To keep this example simple, we’re not including the full output of the `strace`, as it wouldn’t be very useful. In this case, a small allocation for an array of three integers doesn’t trigger the creation of a new large `mmap` region. To see such a result in the trace, we’d need to make a large, explicit allocation on the heap. 

The three integers array will be allocated on the stack. On my Ubuntu system, the default program stack (`ulimit -s` -> 8MB) isn’t created in user space through a direct `mmap` call and does not show up in `strace` output. Instead, the kernel sets up the stack region before transferring control to the program.
