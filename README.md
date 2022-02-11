# Why?
*I got bored with typing "gcc -o file file.c" and "./file"*

*So here is simple C files launcher*

If you are interested in how to apply those colors: [Reddit page](https://www.reddit.com/r/linux/comments/so61ne/i_made_a_tool_to_generate_ansi_escape_codes_so/)

## Usage

Compile it with your favourite compiler

```console
$ git clone https://github.com/9gress0r/wrap-C
$ gcc -o wrap wrap.c
$ ./wrap -w wrap.c
```
## Flags

**"-r"** *flag to run executable after successful compilation*

**"-w"** *flag to toggle all warnings*

**"-d"** *to delete executable after running wrapper*
