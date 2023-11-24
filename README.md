# disass_to_asm
Converts a gcc disassembly output to compilable assembly lines of code.

I may add support for object dumps, but I may put it in a separate public repos to make this one concise.

Either can be the case.


The example in the tests folder was generated as follows:
./disass2asm tests/int_to_str.txt int_to_str tests/word_to_str_ex.txt word_to_str_ex | tee tests/int_word.s

NOTE: I work on a linux machine, but I try my best to make it compatible across other machines
NOTE: the command tee is not natively on Windows, install msys2, then add C:/msys64/usr/bin to path.