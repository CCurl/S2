# S2
S2 is a full-featured, stack-based, Forth-like, interactive, stack-based interpreter/VM, implemented in less than 100 lines of C code.

It was inspired by, and is based on, Sandor Schneider's STABLE program.

S2 supports up to 26 function definitions (A..Z), floating point math, and simple file operations. It also provides 95 registers.
```
************************************
*     S2 Reference                 *
************************************

*** STACK ***
#  (a--a a)       Duplicate TOS           (DUP)
\  (a b--a)       Drop TOS                (DROP)
$  (a b--b a)     Swap top 2 stack items  (SWAP)
%  (a b--a b a)   Push 2nd                (OVER)
_  (a--b)         b: -a                   (NEGATE)


*** ARITHMETIC ***
+   (a b--n)      n: a+b
-   (a b--n)      n: a-b
*   (a b--n)      n: a*b
/   (a b--q)      q: a/b
x%  (a b--m)      m: MODULO(a,b)


*** FLOATING POINT ***
0-9e (--n)        n: a floating point number
f+   (a b--n)     n: a+b
f-   (a b--n)     n: a-b
f*   (a b--n)     n: a*b
f/   (a b--q)     q: a/b
f<   (a b--a f)   f: (a < b) ? -1 : 0;
f>   (a b--a f)   f: (a > b) ? -1 : 0;


*** BIT MANIPULATION ***
b&  (a b--n)      n: a AND b
b|  (a b--n)      n: a OR  b
b^  (a b--n)      n: a XOR b
b~  (a--b)        b: NOT a (ones-complement, e.g - 101011 => 010100)


*** MEMORY ***
@     (a--n)      Fetch INT   n from S2 address a
c@    (a--n)      Fetch BYTE  n from S2 address a
f@    (a--n)      Fetch FLOAT n from S2 address a
m@    (a--n)      Fetch BYTE  n from ABSOLUTE address a
l@    (a--n)      Fetch INT   n from ABSOLUTE address a
!     (n a--)     Store INT   n to S2 address a
c!    (n a--)     Store BYTE  n to S2 address a
f!    (n a--)     Store FLOAT n to S2 address a
m!    (n a--)     Store BYTE  n to ABSOLUTE address a
l!    (n a--)     Store INT   n to ABSOLUTE address a
        NOTE: m!, and l! may cause the virus scanner to freak out.
              If so, you'll need to comment out the (u=='!') part of functions f108() and f109().


*** REGISTERS ***
        NOTES: 1) A register name is any printable character, including <space>
               2) Punctuation characters can also be used registers
rX    (--n)       n: value of register X
sX    (n--)       n: value to store in register X
iX    (--)        Increment register X
dX    (--)        Decrement register X


*** WORDS/FUNCTIONS ***
        NOTES: 1) A function name is a single UPPERCASE character
:     (--)        Define function. Copy chars to (HERE++) until closing ';'.
X     (?--?)      Call function X
^     (--)        Early return from function
;     (--)        Function definition end, return
        NOTES: 1) Returning while inside of a loop is not supported; break out of the loop first.
               2) Use 'xW' to break out of a FOR or WHILE loop.
               2) Use 'xL' to break out of a FOR or WHILE loop.


*** INPUT/OUTPUT ***
.      (n--)      n: Number to output as a decimal
,      (c--)      c: Character to output
b      (--)       Output a SPACE (NOTE: b&, b|, b^, and b~ take precedence)
".."   (--)       Output characters until the next '"'.
0..9   (--n)      Scan DECIMAL number. For multiple numbers, separate them by space (47 33).
        NOTES: 1) To enter a negative number, use "negate" (eg - 490_).
               2) If "e" immediately follows the number (eg - 355e), then it is converted to a float.
'x     (--n)      n: the ASCII value of x
`XXX`  (--)       Executes XXX as a shell command (ie - system(xxx))
?      (--c)      c: next character from STDIN (0 if EOF)


*** CONDITIONS/LOOPS/FLOW CONTROL ***
<     (a b--a f)  f: (a < b) ? -1 : 0;
=     (a b--a f)  f: (a = b) ? -1 : 0;
>     (a b--a f)  f: (a > b) ? -1 : 0;
xU    (--)        UNLOOP: Unwind FOR/WHILE stack, used to return from a function when in a loop 
[     (F T--)     FOR: start a For/Next loop.
xI    (--n)       n: the index of the current FOR loop
xF    (--)        eXit FOR loop: unwind FOR loop stack, continue after next ']'
            NOTE: When in a FOR loop, You can unwind and return from the function using (xUxUxU^)
]     (--)        NEXT: increment index (I) and restart loop if (rI <= T)
{     (f--f)      BEGIN: if (f == 0) skip to matching '}'
}     (f--f?)     WHILE: if (f != 0) jump to matching '{', else drop f and continue
xW    (--)        eXit WHILE loop: unwind WHILE loop stack, continue after next '}'
            NOTE: When in a WHILE loop, you can unwind and return from the function using (xU^)
(     (f--)       IF: if (f != 0), continue into '()', continue after next ')'


*** FILE ***
fO    (n--f)      OPEN  - n: 0=>READ, else WRITE (usage: 0fOh.txt`)
fC    (f--)       CLOSE - f: file handle
fR    (f--f c)    FREAD - f: file handle, c: char read (0 if EOF)
fW    (c f--)     WRITE - f: file handle, c: char to write


*** OTHER ***
xQ    (--)        Exit S2
```
