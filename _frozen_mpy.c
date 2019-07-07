usage: ../micropython/mpy-cross/mpy-cross [<opts>] [-X <implopt>] <input filename>
Options:
-o : output file for compiled bytecode (defaults to input with .mpy extension)
-s : source filename to embed in the compiled bytecode (defaults to input file)
-v : verbose (trace various operations); can be multiple
-O[N] : apply bytecode optimizations of level N

Target specific options:
-msmall-int-bits=number : set the maximum bits used to encode a small-int
-mno-unicode : don't support unicode in compiled strings
-mcache-lookup-bc : cache map lookups in the bytecode
-march=<arch> : set architecture for native emitter; x86, x64, armv6, armv7m, xtensa

Implementation specific options:
  emit={bytecode,native,viper} -- set the default code emitter
  heapsize=<n> -- set the heap size for the GC (default 2097152)
