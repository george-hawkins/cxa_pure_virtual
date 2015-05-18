Why doesn't nano provide a slimmer __cxa_pure_virtual?

I wrote a tiny demo program that deliberately pulls in __cxa_pure_virtual.

If I replace the "= 0;" of the single pure virtual method in this demo with "{ }" then the size of the .text section (as reported by "size -A") drops really dramatically.

I'm definitely using nano - if I remove "--specs=nano.specs" from my linker arguments then I see a noticeable size increase.

Why doesn't nano provide a slimmer __cxa_pure_virtual by default?

At the moment I have to add the following to every program to avoid this cost:

extern "C" void __cxa_pure_virtual() { abort(); }

I suspect I'm missing something here, is there a flag I should be using or such like to avoid this?

I've put together a small demo on GitHub if you want to experiment with this:

https://github.com/george-hawkins/cxa_pure_virtual

The file there called demo.cpp contains a class Foo that has a pure virtual method if the macro PURE_VIRTUAL is defined.

I've provided a little bash script called BUILD that will build everything and output the size of the .text section.

The following shows cloning the repo and building first with PURE_VIRTUAL unset and then with it set:

$ git clone git@github.com:george-hawkins/cxa_pure_virtual.git
$ cd cxa_pure_virtual
$ ./BUILD
360
$ ./BUILD --pure
47132
$ ./BUILD --pure-stubbed
3096

The final BUILD call above shows using a pure virtual but with __cxa_pure_virtual stubbed to be:

extern "C" void __cxa_pure_virtual() {
    puts("__cxa_pure_virtual() called - see https://goo.gl/YJXrK3");
    abort();
}

As you can see the size output grows from 524 to 47132 when a pure virtual is used and then shrinks back down to 3096 if a lighter weight __cxa_pure_virtual is used.

If I remove the "puts" line from the __cxa_pure_virtual function the size reduces down to just 524.

Note: demo.cpp just demos this issue, it doesn't make any real sense, some of the code is there just to make sure things don't get optimized away.

The other files are:
* reset.c - this provides the main entry point and most importantly calls __libc_init_array.
* syscalls.c - this provides the functions like _kill that are called by _kill_r etc. in libc.
* RBL_nRF51822.ld - this is the short linker script for the system I'm using (a RBL BLE Nano).

I cut everything down to a minimum but don't know enough about linker scripts - so it's the unchanged original.

The above byte values, i.e. 524, 47132, 3096 and 524 were generated when using the 4.9.3 arm-none-eabi-g++ from Terry Guo's PPA.

If I use 4.8.3 that comes with the 1.6.4 Arduino IDE the corresponding sizes are 368, 35532, 3048 and 540 respectively.

I.e. things have gotten bigger between 4.8.3 and 4.9.3.

Thanks,

/George
