# DNLF.x86
<ins>a refactor and cross-platform port of [DO NOT LOSE FOCUS by X Future](https://github.com/0xf0000629/DONOTLOSEFOCUS)</ins>

right now, only the gameplay part is done - the next stage will be figuring out how to make all of the malware-esque stuff happen

## why?
cause i think DNLF is a really cool game, gameplay-wise its not the best but holy shit the aesthetic goes HARD

## building and running
clone the repo with `git clone https://github.com/ana-rchy/dnlf.x86 --recurse-submodules`

### <ins>linux</ins>
make sure you have `raylib` installed on your system (it'll most likely be in your distro's package repository)

then, <br>
`make main` to build, or <br>
`make run` to run <br>
you can also <br>
`make debug` and `make run-debug` to build with debugging flags and run with gdb

### <ins>windows</ins>
`make windows` to build <br>
move the .exe from `output/` into the main directory <br>
then run
