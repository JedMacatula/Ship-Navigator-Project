I ran each input file with stack mode, sending the output to a file.
I used the time command and the results are shown below.

NOTE that different machines and compile flags can have significantly
different times!  Don't time code by hand inside of Visual Studio or
Xcode, as these IDEs usually use a debug build rather than one
optimized for speed.

User times:
Big, L to M: 0.908s
Big, M to M: 0.187s
Big, L to L: 0.802s
Big, M to L: 0.082s

Small, L to M: 0.006s
Small, M to M: 0.003s
Small, L to L: 0.006s
Small, M to L: 0.002s
