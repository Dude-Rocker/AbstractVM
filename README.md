## [Abstract VM](https://github.com/Dude-Rocker/resources/blob/master/pdf-s/abstract-vm.pdf)
## The project school 42 of C++ branch
#### The purpose of this project is to create a simple virtual machine that can interpret programs, it will run some basic arithmetic programs coded in a very basic assembly language. *If you want to have an idea of what the program’s capabilities should look like, type the command man dc in your shell.*
### The language of AbstractVM is composed of a series of instructions, with one instruction per line and he has a limited type system:
* **;** - comment
* **push v** - Pushes the value v at the top of the stack. The value v must have one of the following form:
  * **int8(n)** : Creates an 8-bit integer with value n.
  * **int16(n)** : Creates a 16-bit integer with value n.
  * **int32(n)** : Creates a 32-bit integer with value n.
  * **float(z)** : Creates a float with value z.
  * **double(z)** : Creates a double with value z.
* **pop** - Unstacks the value from the top of the stack.
* **dump** - Displays each value of the stack, from the most recent one to the oldest one WITHOUT CHANGING the stack.
* **assert v** - Asserts that the value at the top of the stack is equal to the one passed as parameter for this instruction.
* ***next instructions unstacks the first two values on the stack, run arithmetic programs, then stacks the result:***
  * **add** - adds.
  * **sub** - subtracts.
  * **mul** - multiplies
  * **div** - divides
  * **mod** - calculates the modulus
* **print** - Asserts that the value at the top of the stack is an 8-bit integer. Then interprets it as an ASCII value and displays the corresponding character on the standard output.
* **exit** - Terminate the execution of the current program.
