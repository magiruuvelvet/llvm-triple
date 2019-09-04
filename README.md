# llvm-triple

Small command line frontend for LLVM's target triple parser.

## Requirements

 - LLVM (`LLVMSupport`)

## Usage

```
llvm-triple [options] <target triple>
```

If the target triple is omitted, than the default target for
the currently active LLVM installation is used.

To get verbose information about a target triple and how LLVM
processes this internally use the `--verbose` (`-v`) switch.

## Example Outputs

```plain
$ llvm-triple
Triple:                       x86_64-pc-linux
Valid Triple:                 yes
Operating System:             Linux
Operating System Version:     unspecified
Architecture:                 x86_64
Address Model:                64-bit
Vendor:                       Generic PC
Environment:                  unknown
Environment Version:          unspecified
Endianess:                    Little Endian
Object Format:                ELF
```

```plain
$ llvm-triple x86_64-unknown-freebsd12.0
Triple:                       x86_64-unknown-freebsd12.0
Valid Triple:                 yes
Operating System:             FreeBSD
Operating System Version:     12.0.0
Architecture:                 x86_64
Address Model:                64-bit
Vendor:                       unknown
Environment:                  unknown
Environment Version:          unspecified
Endianess:                    Little Endian
Object Format:                ELF
```

```plain
$ llvm-triple arm64-apple-ios12
Triple:                       arm64-apple-ios12
Valid Triple:                 yes
Operating System:             Apple iOS
Operating System Version:     12.0.0
Architecture:                 aarch64
Address Model:                64-bit
Vendor:                       Apple
Environment:                  unknown
Environment Version:          unspecified
Endianess:                    Little Endian
Object Format:                Mach-O
```

```plain
$ llvm-triple x86_64-pc-windows
Triple:                       x86_64-pc-windows-msvc
Valid Triple:                 yes
Operating System:             Microsoft Windows
Operating System Version:     unspecified
Architecture:                 x86_64
Address Model:                64-bit
Vendor:                       Generic PC
Environment:                  Microsoft Visual C/C++ Runtime
Environment Version:          unspecified
Endianess:                    Little Endian
Object Format:                COFF
```
