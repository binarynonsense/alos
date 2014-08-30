ALOS - Álvaro's Operative System
================================

A simple operative system I created some years ago in order to learn more about computers.

This project is based on the kernel tutorials by JamesM (http://www.jamesmolloy.co.uk/tutorial_html/index.html) and Brandon F (http://www.osdever.net/bkerndev/index.php), and the really helpful OSDev.org wiki and forums.

Last things I added were a simple command line interface and a very basic VGA driver (not finished).

Once built, it includes a makefile, you can use QEMU to test it: qemu-system-i386 -kernel oskernel -soundhw pcspk

Video: https://www.youtube.com/watch?v=4JsgIdO43SU