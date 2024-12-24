kruft
=====
My personal collection of functions used for working on crufty C and C++
codebases.

- Support C89 and C++98 compilers, and possibly a few older pre-standard
  fossils.
- Support C++11 `constexpr` when possible.
- Implementations prefer clarity over cleverness.
- No dependencies except compiler headers and a possibly-incomplete but
  non-hostile C89 libc.
- Very few transitive header dependencies.
- If you want to copy and paste an implementation, converting kruft's defines
  and types to your project or compiler's equivalents should be easy.
- Extensively tested with my single-header test framework **zztest**.
- Permissively licensed; only source-code attribution required.

How to use
----------
The headers are inside the `include` directory, and can simply be dropped
inside your project.  There _is_ a `CMakeLists.txt`, but it mostly exists
in order to run the test suite and benchmarks.  Additionally, there are a
few Makefiles inside the `test` directory if you want to run the test suite
in your own environment that doesn't have CMake support.

Compiler Support
----------------
Since this library is designed for crusty codebases, it is intended to work
in crufty compilers as well.  Currently, it is being tested in:

- Modern GCC/Clang/MSVC
- Visual C++ 6.0
- Borland C++ 3.1 for DOS
- WATCOM C 9.01 for DOS

If you have a compiler that this project does not work in, or if any test
case fails in your environment, file an Issue or submit a Pull Request.

Limitations
-----------
Note that although this library is designed for crufty compilers and
environments, there are certain limitations.  Code legibility is prioritized
above compatibility - each function should be legible enough to allow for
vendoring into your own codebases and having them work while only changing
around a few kruft-specific defines.

If your environment has constraints that preclude the use of certain functions
due to needing too much ROM space, using too much stack, or being inordinately
slow on a particular architecture, feel free to open a pull request with your
version of the function.  Don't replace the existing function, make a second
function that documents the justification for its existence.

On the other hand, if your environment is crufty to the point of needing
library-wide disruptive changes, such as needing K&R function declaration
syntax, or working around a compiler-specific bug, this would be outside
the scope of kruft unless it's something that could be easily shimmed.

zztest
------
The test suite is driven by a single-header test framework of my own creation
called **zztest**.  It is inspired by Google Test, but is written in C89 and
works in similarly crufty environments to kruft itself, while also not
depending on kruft.  Feel free to use it to test your own C programs, though
if you want to test in a reasonably modern compiler, you should probably be
using Google Test, Catch or some other framework written in C++.

License
-------
[Boost Software License](LICENSE.txt).  Unlike the MIT, BSD or Apache license,
it only requires attribution in the source code, not in distributed binaries.
It also has no form of GPL-style copyleft.
