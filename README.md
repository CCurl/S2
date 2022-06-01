# S2
S2 is a full-featured and interactive stack-based interpreter/VM, implemented in less than 100 lines of C code.

It was inspired by, and is based on, Sandor Schneider's STABLE program.

S2 supports up to 26 function definitions (A..Z), floating point math, and simple file operations. It also provides 95 registers.

## Examples
```
0(this is a comment)
"Hello World!"        0("Hello World!")
:N10,;                0(define function N)
10_ 10[n.b]           0(print out numbers from -10 through 10)
#("yes")~("no")       0(print "yes" or "no" depending on TOS)
r1 fO#(fR{,fR}fC)     0(print the contents of the file named by r1)
123 {#.b1-}           0(count down and print out from 123 to 0)
355e 113e f/ F.       0(floating point - PI)
32 126[n.": "n.,N]    0(print the ascii table)
```
## S2 Reference
```
*** STACK ***
#  (a--a a)       Duplicate TOS             (DUP)
\  (a b--a)       Drop TOS                  (DROP)
$  (a b--b a)     Swap top 2 stack items    (SWAP)
%  (a b--a b a)   Push 2nd                  (OVER)
_  (a--b)         b: -a                     (NEGATE)


*** ARITHMETIC ***
+   (a b--n)      n: a+b
-   (a b--n)      n: a-b
*   (a b--n)      n: a*b
/   (a b--q)      q: a/b
&   (a b--q r)    q:: DIV(a,b), r:MOD(a,b)  (/MOD)
x%  (a b--r)      r: MOD(a,b)


*** FLOATING POINT ***
0-9e (--n)        n: a floating point number
ff   (a--b)       b: int a converted to float
fi   (a--b)       b: float a converted to int
f+   (a b--n)     n: a+b
f-   (a b--n)     n: a-b
f*   (a b--n)     n: a*b
f/   (a b--q)     q: a/b
f<   (a b--a f)   f: (a < b) ? -1 : 0;
f>   (a b--a f)   f: (a > b) ? -1 : 0;
fs   (a--b)       b: SQRT(a)
ft   (a--b)       b: TANH(a)


*** BIT MANIPULATION ***
b&  (a b--n)      n: a AND b
b|  (a b--n)      n: a OR  b
b^  (a b--n)      n: a XOR b
b~  (a--b)        b: NOT a (ones-complement, e.g - 11001011 => 00110100)


*** MEMORY ***
        USAGE: ints:  [0- 64:stacks][ 65- 90:funcs][100-199:regs][200-1749:free][1750-2499:code]
               bytes: [0-259:stacks][260-359:funcs][400-799:regs][800-6999:free][7000-9999:code]
@     (a--n)      Fetch INT   n from S2 address a
c@    (a--n)      Fetch BYTE  n from S2 address a
f@    (a--n)      Fetch FLOAT n from S2 address a
!     (n a--)     Store INT   n to S2 address a
c!    (n a--)     Store BYTE  n to S2 address a
f!    (n a--)     Store FLOAT n to S2 address a


*** LOCALS ***
l+    (--)        Allocate 10 locals
l-    (--)        De-allocate 10 locals
lX    (--a)       Push address of local #X

*** REGISTERS ***
        NOTES: 1) A register name is any printable character, including <space>
               2) Punctuation characters can also be used registers
rX    (--n)       Read value of register X (n)
sX    (n--)       Store (n) in register X
iX    (--)        Increment register X
iX@   (--n)       n: value of register X BEFORE incrementing it
dX    (--)        Decrement register X
dX@   (--n)       n: value of register X BEFORE decrementing it


*** WORDS/FUNCTIONS ***
        NOTES: 1) A function name is a single UPPERCASE character.
:X    (--)        Define function X. Copy chars to (HERE++) until closing ';'.
X     (?--?)      Call function X.
;     (--)        Function definition end, (when running, return).
^     (--)        Early return from function.
        NOTES: 1) When in a WHILE loop, unwind the loop stack first using (xU^)
               2) When in a FOR loop, unwind the loop stack first using (xUxUxU^)


*** INPUT/OUTPUT ***
.      (n--)      n: Number to output as a decimal
,      (c--)      c: Character to output
b      (--)       Output a single SPACE (NOTE: b&, b|, b^, and b~ take precedence)
".."   (--)       Output characters until the next '"'.
0..9   (--n)      Scan DECIMAL number n. For multiple numbers, separate them by space (47 33).
        NOTES: 1) To enter a negative number, use "NEGATE" (eg - 490_).
               2) If "e" immediately follows the number (eg - 355e), then n is converted to a float.
'x     (--n)      n: the ASCII value of x
`XXX`  (--)       Executes XXX as a shell command (ie - system(xxx))
|XXX|  (A--B)     Copies XXX<NULL> to BYTE address A. B: Next char after the <NULL>
?      (--c)      c: next character from STDIN (0 if EOF)


*** CONDITIONS/LOOPS/FLOW CONTROL ***
<     (a b--f)    f: (a <  b) ? -1 : 0;
=     (a b--f)    f: (a == b) ? -1 : 0;
>     (a b--f)    f: (a >  b) ? -1 : 0;
<=    (a b--f)    f: (a <= b) ? -1 : 0;
>=    (a b--f)    f: (a >= b) ? -1 : 0;
~     (a--f)      f: (a == 0) ? -1 : 0;  (Logical NOT)
(     (f--)       IF: if (f != 0), continue into '()', else jump to next ')'
[     (F T--)     FOR: start a FOR/NEXT loop.
]     (--)        NEXT: increment index (I) and restart loop if (rI <= T)
n     (--n)       n: the index of the current FOR loop iterator
p     (N--)       Add N to the current FOR loop iterator
xF    (--)        eXit FOR loop: unwind FOR loop stack, jump to next ']'
{     (f--f)      BEGIN: if (f == 0) jump to matching '}'
}     (f--f?)     WHILE: if (f != 0) jump to matching '{', else drop f and continue
xW    (--)        eXit WHILE loop: unwind WHILE loop stack, continue after next '}'
xU    (--)        Remove the top entry from the return stack.
        NOTES: 1) This can be used to return from the function while in a loop.
               2) A WHILE loop puts ONE entry on the return stack.
               3) A FOR loop puts 3 entries on the return stack.
e     (A--)       EXECUTE: call function at location A


*** FILE ***
fO    (a n--f)    OPEN  - n: 0=>READ, else WRITE (usage: 1000 0fO)
fC    (f--)       CLOSE - f: file handle
fR    (f--f c)    FREAD - f: file handle, c: char read (0 if EOF)
fW    (c f--)     WRITE - f: file handle, c: char to write


*** OTHER ***
t     (--n)       n: clock()
q     (--)        Prints the stack
xQ    (--)        Exit S2
```
