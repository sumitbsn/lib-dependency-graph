# lib-dependency
It's a Unix/Linux Utility to find the library dependencies of a program.

To invoke the program – $libdd "Input program path"

Example:- $libdd /usr/bin/vlc

output: 
********************************************************TABLE VIEW OF LIBRARY DEPENDENCY************************************************
vlc                  ->          libvlc.so.5     libpthread.so.0          libdl.so.2           libc.so.6
libvlc.so.5          ->      libvlccore.so.7     libpthread.so.0           libc.so.6
libvlccore.so.7      ->           librt.so.1        libidn.so.11     libpthread.so.0          libdl.so.2           libm.so.6      libdbus-1.so.3           libc.so.6
librt.so.1           ->      libpthread.so.0           libc.so.6
libpthread.so.0      ->            libc.so.6       ld-linux.so.2
libc.so.6            ->        ld-linux.so.2
libidn.so.11         ->            libc.so.6
libdl.so.2           ->            libc.so.6       ld-linux.so.2
libm.so.6            ->            libc.so.6       ld-linux.so.2
libdbus-1.so.3       ->      libpthread.so.0          librt.so.1           libc.so.6
********************************************************************END*****************************************************************
