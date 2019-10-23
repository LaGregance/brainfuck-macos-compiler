# Brainfuck MacOS Compiler (BFC)
A home made brainfuck compiler for MacOS (tested on Mojave).

## What is brainfuck
Brainfuck is an esoteric programming language. It's a very simple language (there is only 8 instructions) but hard to decode for an human.
You can learn more about brainfuck by following this link : https://en.wikipedia.org/wiki/Brainfuck

## How to use Brainfuck MacOS Compiler
1. Clone the project
2. Make it
3. Run it with ./bfc <source_file> [-o <output_file>]
4. Enjoy your fully compiled program !

## How it's work
1. BFC read your source file and write a temporary assembly file
2. Next, it call nasm to make object file
3. Finally, it call ld to link the object in an executable file

## Limitations
The instruction ```,``` (to get a char from stdin) isn't implemented yet and will be see as comment
