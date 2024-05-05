# reprom

A small tool to locate chunks of unwritten space on OTP EPROMs for reusing them.

## Usage

```
$ make reprom

$ reprom <file> <address lines>

file is the image of an OTP eprom obtained with a programmer/reader
address lines is the number of desired address lines available (1 is 2 bytes, 2 is 4 bytes ...)
```

The program will then output (if any) the free chunks available for the number of address lines requested, with the offset in the file and the wiring of the EPROM for using this chunk

## Limitations

This program does not check for free space with arbitrary permutations of the address lines.
