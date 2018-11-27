
# Programming Python3 Notes  
by zcatt, Feb2018

# 主要章节
* 一些基本知识
* module and package
* Classes and OOP
* Built-in functions
* Built-in constants
* Built-in Types
* ref


# 一些基本知识

## Object ，variable name， and dynamic typing
---
variable使用名字name标识，variable通过link与object关联。在python中object是实际操作的对象， variable仅仅是object的hanlde。 variable本身不具type信息，而type信息是object所持有。  
也就是说,variable是symbol table中的一个项，object是memory中的一段空间, 而reference是关联variable和object的指针。

一个语句的背后  
```
    a= 3
```    
1. 创建对象表示3
2. 创建variable a
3. 将variable a连接到对象.

In python types are determined automatically at runtime, not in response to declarations in your code.

## Scope and LEGB rules
---
python中有几类scope， function定义的local scope, module定义的global scope, 
    1.The enclosing module is a global scope.
    2.The global scope spans a single file only.
    3.Assigned names are local unless declared global or nonlocal.
    4.All other names are enclose function locals, globals, or built-ins.
    5.Each call to a function creates a new local scope.


LEGB rules  
1. When you use an unqualified name inside a function, Python searches up to four scopes—the local (L) scope, then the local scopes of any enclosing (E) defs and lambdas, then the global (G) scope, and then the built-in (B) scope—and stops at the first place the name is found. If the name is not found during this search, Python
reports an error.
2. When you assign a name in a function (instead of just referring to it in an expression),  Python always creates or changes the name in the local scope, unless it’s declared to be global or nonlocal in that function.
3. When you assign a name outside any function (i.e., at the top level of a module file, or at the interactive prompt), the local scope is the same as the global scope— the module’s namespace.

## unicode and byte strings
---
python 2中的str和unicode对应到python3的bytes和str。另外python3引入的bytearray.  
在python3中,
* str 表示decoded unicode text(including ASCII). an immutable sequence of characters.
* bytes表示binary data(including encoded text). an immutable sequence of 8-bit integers.
* bytearray, a mutable flavor of the bytes type. a mutable sequence of 8-bit integers which supports in-place changes.

examples,  

    C:\code> C:\python33\python
    >>> B = b'spam' # 3.X bytes literal make a bytes object (8-bit bytes)
    >>> S = 'eggs' # 3.X str literal makes a Unicode text string
    >>> type(B), type(S)
    (<class 'bytes'>, <class 'str'>)
    >>> B # bytes: sequence of int, prints as character string
    b'spam'
    >>> S
    'eggs'    

### string type conversion  
---
3.X draws a much sharper distinction— str and bytes type objects never mix automatically in expressions and never are converted to one another automatically when passed to functions. A function that expects an argument to be a str object won’t generally accept a bytes, and vice versa.
* str.encode() and bytes(S, encoding) translate a string to its raw bytes form and        create an encoded bytes from a decoded str in the process.
* bytes.decode() and str(B, encoding) translate raw bytes into its string form and        create a decoded str from an encoded bytes in the process.    

## BOM
---
coding  |   note        
------|----
utf-8 |                 utf8 without BOM
utf-8-sig |             utf8 with BOM
utf-16 |                utf16 with BOM
utf-16-be |             utf16 bigendien without BOM 
utf-16-le |             utf16 littleendien without BOM 
utf-16-less |           utf16 without BOM


如下例子,

    C:\code> C:\python33\python # File saved in Notepad
    >>> import sys
    >>> sys.getdefaultencoding()
    'utf-8'
    >>> open('spam.txt', 'rb').read() # ASCII (UTF-8) text file
    b'spam\r\nSPAM\r\n'
    >>> open('spam.txt', 'r').read() # Text mode translates line end
    'spam\nSPAM\n'
    >>> open('spam.txt', 'r', encoding='utf-8').read()
    'spam\nSPAM\n'

    >>> open('spam.txt', 'rb').read() # UTF-8 with 3-byte BOM
    b'\xef\xbb\xbfspam\r\nSPAM\r\n'
    >>> open('spam.txt', 'r').read()
    'ï»¿spam\nSPAM\n'
    >>> open('spam.txt', 'r', encoding='utf-8').read()
    '\ufeffspam\nSPAM\n'
    >>> open('spam.txt', 'r', encoding='utf-8-sig').read()
    'spam\nSPAM\n'

    >>> open('spam.txt', 'rb').read()
    b'\xfe\xff\x00s\x00p\x00a\x00m\x00\r\x00\n\x00S\x00P\x00A\x00M\x00\r\x00\n'
    >>> open('spam.txt', 'r').read()
    '\xfeÿ\x00s\x00p\x00a\x00m\x00\n\x00\n\x00S\x00P\x00A\x00M\x00\n\x00\n'
    >>> open('spam.txt', 'r', encoding='utf-16').read()
    'spam\nSPAM\n'
    >>> open('spam.txt', 'r', encoding='utf-16-be').read()
    '\ufeffspam\nSPAM\n'


    >>> open('temp.txt', 'w', encoding='utf-8').write('spam\nSPAM\n')
    10
    >>> open('temp.txt', 'rb').read() # No BOM
    b'spam\r\nSPAM\r\n'
    >>> open('temp.txt', 'w', encoding='utf-8-sig').write('spam\nSPAM\n')
    10
    >>> open('temp.txt', 'rb').read() # Wrote BOM
    b'\xef\xbb\xbfspam\r\nSPAM\r\n'
    >>> open('temp.txt', 'r').read()
    'ï»¿spam\nSPAM\n'
    >>> open('temp.txt', 'r', encoding='utf-8').read() # Keeps BOM
    '\ufeffspam\nSPAM\n'
    >>> open('temp.txt', 'r', encoding='utf-8-sig').read() # Skips BOM
    'spam\nSPAM\n'


## module and package
---
首先要明确，module和package自身在python中也是一个object.  
Module statements run on the first import. reload语句会重新载入和执行module statements.  
Top-level assignments create module attributes.  
Module namespaces can be accessed via the attribute __dict__ or dir(M).  
Modules are a single scope(local is global).  


## import statement
---
几种形式的import

    import module1 
    from module1 import a as A， b as B 
    from module1 import *

module file中的top-level code仅在第一次import时执行一次。

## package __init__.py files
---
package目录下应当包含__init__.py文件用于标识该目录是package。   
__init__.py定义了package的初始化动作。包括
* package initialization
* module usability declarations
* module namespace initialization 
* from *语句。 定义__all__，声明import from *该package时应当默认载入的modules.








# Classes and OOP
python中class也是object，即class使用class object代表。而instance是instance object. class实际上是instance的factory.

## unbound method and bound method 
---
同样method也是object，分作unbound method和bound method. 所谓bound method是指method object已经含有instance object的信息，调用其时，不需再提供self参数. 而unbound method实际就是function in python 3.

    class Spam:
        def doit(self, message):
        print(message)

    object1 = Spam()
    x = object1.doit # Bound method object: instance+function
    x('hello world') # Same effect as object1.doit('...')

    object1 = Spam()
    t = Spam.doit # Unbound method object (a function in 3.X: see ahead)
    t(object1, 'howdy') # Pass in instance (if the method expects one in 3.X)


## staticmethod and classmethod
---
classmethod入口参数带cls object, 而static method不带。

    class Methods:
        def imeth(self, x): # Normal instance method: passed a self
            print([self, x])

        def smeth(x): # Static: no instance passed
            print([x])

        def cmeth(cls, x): # Class: gets class, not instance
            print([cls, x])

        smeth = staticmethod(smeth) # Make smeth a static method (or @: ahead)
        cmeth = classmethod(cmeth) # Make cmeth a class method (or @: ahead)


## decoration
---
decoration形式上类似于java的注记. Decoration is a way to specify management or augmentation code for functions and
classes. Decorators themselves take the form of callable objects (e.g., functions) that
process other callable objects. 
Decorator can be used as call proxy or interface proxy.

有两种decorators， function decorator和class decorator.
    class C:
        @staticmethod # Function decoration syntax
        def meth():
        ...

等价于
    class C:
        def meth():
            ...
        meth = staticmethod(meth) # Name rebinding equivalent

一个例子，
    class Methods(object): # object needed in 2.X for property setters
        def imeth(self, x): # Normal instance method: passed a self
            print([self, x])
    
        @staticmethod
        def smeth(x): # Static: no instance passed
            print([x])

        @classmethod
        def cmeth(cls, x): # Class: gets class, not instance
            print([cls, x])

        @property # Property: computed on fetch
        def name(self):
            return 'Bob ' + self.__class__.__name__

    >>> from bothmethods_decorators import Methods
    >>> obj = Methods()
    >>> obj.imeth(1)
    [<bothmethods_decorators.Methods object at 0x0000000002A256A0>, 1]
    >>> obj.smeth(2)
    [2]
    >>> obj.cmeth(3)
    [<class 'bothmethods_decorators.Methods'>, 3]
    >>> obj.name
    'Bob Methods'


user-defined function decorator

    class tracer:
        def __init__(self, func): # Remember original, init counter
            self.calls = 0
            self.func = func

        def __call__(self, *args): # On later calls: add logic, run original
            self.calls += 1
            print('call %s to %s' % (self.calls, self.func.__name__))
            return self.func(*args)

        @tracer # Same as spam = tracer(spam)
        def spam(a, b, c): # Wrap spam in a decorator object
            return a + b + c
        
    print(spam(1, 2, 3)) # Really calls the tracer wrapper object
    print(spam('a', 'b', 'c')) # Invokes __call__ in class


## metaclass
---
TODO  
metaclass可以控制class object的创建过程。


# Built-in functions

## Number and math
---
func | note
------|----------  
abs()  | absolute or magnititude value 
complex() | return a complex number.
bin() oct hex() | convert an integer number to a lowercase binary , otal or hexadecimal string with '0b' , '0o' or '0x'
float() int() | return a float or int derived from a number or string
min() max() | return minimur or maximum.
divmod() | return a pair of quotient and reminder
pow(x,y[,z]) | (x^y) % z
round() | 保留到指定精度
sum() | 求和

## Character and string
---
func | note
---|---
ascii() | return a printable string of an object, but escape the non-ascii characters using \x, \u or \U escapes.
bytearray() | return a new mutable array of bytes.
bytes() | return a new immutable bytes object.
chr() | input unicode code point, output a string representing a character.
ord() | input a string representing one unicode character, output unicode code point.
repr() | return a string of an object.
str() | return a str version of object.

## Iterable and collection
---
func | note
---|---
all() | True if all elements of the iterable are true.
any() | True if any element of the iterable is true.
dict() | create a new dictionary.
dir([obj]) | return a list of name in the current local scope when no argument, a list of valid attributes for the object when one object arg is given.
enumerator(iterable, start=0) | Return an enumerate object. enumerate object的__next__()返回一个[序数，value]形式的tuple.
filter(function, iterable) | 构造一个iterator, 元素包括iterable中function取值true的元素。等价于(item for item in iterable if function(item))
iter() | return an iterator object.
len() | return the length of a sequence or a collection.
list() | return a list.
set() | return a new set object.
map() | return an iterator.
next() | retrieve the next item from the iterator
object | return a new featureless object
range() | range is actually an immutable sequence type.
reverse() | return a reverse iterator.
slice() |
sorted() | return a NEW sorted list from the items in iterable.
tuple() |
zip(*iterables) | Make an iterator that aggregates elements from each of the iterables.




```
>>> seasons = ['Spring', 'Summer', 'Fall', 'Winter']
>>> list(enumerate(seasons))
[(0, 'Spring'), (1, 'Summer'), (2, 'Fall'), (3, 'Winter')]
>>> list(enumerate(seasons, start=1))
[(1, 'Spring'), (2, 'Summer'), (3, 'Fall'), (4, 'Winter')]
```

```
>>> x = [1, 2, 3]
>>> y = [4, 5, 6]
>>> zipped = zip(x, y)
>>> list(zipped)
[(1, 4), (2, 5), (3, 6)]
>>> x2, y2 = zip(*zip(x, y))
>>> x == list(x2) and y == list(y2)
True
```


## Attribute
---
func | note
---|---
delattr() | Delete an attribute from the object.
getattr() | Return the value of the named attribute of object.
hasattr() | True if the object has the the name attribute.
property() | return a property attribute.
setattr() | 


## object and type
---
func|note
---|---
hash() | calc hash value.
id() | identity of an object.
isinstance() | True if be instance.
issubclass() |
super() | return a proxy object that delegates method calls to a parent or sibling class of type. 
type(object) |
type(name, bases, dict) |


## other
---
func|note
---|---
bool() | the boolean value
callable() | True if the object arg appears callable.
@classmethod | Transform a method into a class method.
@staticmethod |
compile() | Compile one source into a code or AST object. Code objects can be executed by exec() or eval()
eval() | Parse and evaluated one expression.
exec() | dynamic execution of python code.
format() | 输出格式化的表示.
frozenset() |
globals() | 返回一个dictionary, 内容是当前global symbol table。
locals() | 返回一个dictionary, 内容是当前local symbol table。
help() | 
input() | read a line from input.
open() | open file and return a corresponding file object.
print() | print objects to the text stream file.
vars() | return the __dict__ attribute for a module, class, instance, or any other object with a __dict__ attribute.
__import__() |


# Built-in constants

constants | note
---|---
False | value of bool type
True | value of bool type
None | value of the NoneType type
NotImplemented | 
Ellipsis | used mostly in contjunction with extended slicing syntax for user-defined container data types.
\_\_debug\_\_ | this constant is true if python was not started with an -O option.

# Built-in Types
The principal built-in types are numerics, sequences, mappings, classes, instances and exceptions.

## Truth value testing
---

Any object can be tested for truth value. Here are most of the built-in objects considered false:
* None and False
* zero of any numeric type: 0, 0.0, 0j, Decimal(0), Fraction(0,1)
* empty sequences and collections: '', (), [], {}, set(), rang(0)


## Numeric Types: int, float, complex
---
int, float and complex are three distinct numeric types in python. Booleans are a subtype of integers. fractions holds rationals, and decimal hold floating-point numbers with user-defined precision.

### Some Methods on Integer Types
method | note
---|---
bit_length() | the number of bit necessary an integer n binary, 不含符号位和前导0.
to_bytes() | return an array of bytes representing an integer
from_bytes() | Return the integer represented by the given array of bytes.

### Some Methods on Integer Float

method | note
---|---
as_integer_ration() | 返回一对整数，其比值是float。
is_integer() | True if be integer
float_hex() | 
fromhex()| 

## Iterator Types
---
The container should define __iter__() method to provide iteration support.  
The iterator object should support two methods.

method | note
---|---
iterator.__iter__() | return the iterator object itself.
iterator.__next__() | return the next item from the container. If no further items, raise the StopIteration exception.

container.__iter__() can be implemented as a generator, it will auto return an iterator object.

## Sequence Types: list, tuple, range
---
### immutable and mutable sequence都支持的操作。
operation | note
---|---
x in s |
x not in s |
s + t | concatenation
s*n or n*s | concatenation of s n times
s[i] | ith item
s[i:j] | slice from i to j
s[i:j:k] | slice with step k
len(s) | number of items
min(s) | smallest item
max(s) | largest item
s.index(x[, i[,j]]) | index of the first occurence of x ins
s.count(x) | total number of occurrences of x in s

index取值<0时，则以len(s)为基点，注意-0是0.

### 仅mutable sequence支持的操作.
operation | note
---|---
s[i] = x |
s[i:j] = t |
del s[i:j] |
s[i:j:k] = t | 指定元素替换为序列t中的元素
del s[i:j:k] |
s.append(x) | 追加元素
s.clear() | same as del[:]
s.copy() |
s.extend(t) or s += t | 追加序列
s *= n | 重复扩展
s.insert(i,x) | same as s[i:i] = x
s.pop([i]) | retrieve and remove
s.remove(x) | 删除序列中第一个出现的与x相等的元素
s.reverse() | 倒序。

list是mutable sequence. list支持sort()方法.  
tuple是immutable sequence.  
range是immutable的，表示了一个数字序列。

## Sequence types, str
---
String is immutable sequence of Unicode code points.

class str(object='')  
class str(object=b'', encoding='utf-8', errors='strict')  

str()采用以上两形式，会返回object的string，首先是object.__str__()，若该方法为定义，则返回repr(object).  

### String methods

method | note
---|---
str.capitalize() | a copy of 首字母大写
str.casefold() | return a casefolded copy
str.center(width[,fillchar]) | centered in a string of length width. padding is done using the specified fillchar.
str.count(sub[,start[,end]]) | 子串出现的次数.
str.encode(encoding="utf-8", errors="strict") | return a byte object.
str.endswith(suffix[,start[,end]]) | True if end with suffix.
str.expandtabs(tabsize=8) | return a copy where all tab are replaced by one or more spaces.
str.find(sub[,start[,end]]) | 查找字串的第一次出现位置。
str.format(*args, **kwargs) | see below.
str.format_map(mapping) |
str.index(sub[,start[,end]]) | Like find().
str.isalnum() | 
str.isalpha() |
str.isdecimal() |
str.isdigit() |
str.isidentifier() |
str.islower() |
str.isnumeric() |
str.isprintable() |
str.isspace() |
str.istitle() |
str.isupper() |
str.join(iterable) |
str.ljust(width[,fillchar]) |
str.lower() |
str.lstrip([chars]) | return a copy with leading characters removed.
static str.maketrans(x[,y[,z]]) |
str.partition(sep) | split the string at the first occurence of sep, and return a 3-tuple.
str.replace(old,new[,count]) |
str.rfind(sub[,start[,end]]) |
str.rindex(sub[,start[,end]]) |
str.rjust(width[,fillchar]) |
str.rpartition(sep) |
str.rsplit(sep=None, maxsplit=-1) | 
str.rstrip([chars]) | return a copy with trailing characters removed.
str.split(sep=None, maxsplit=-1) |
str.splitlines([keepends]) |return a list of the lines in the string. 
str.startswith(prefix[,start[,end]]) |
str.strip([chars]) |
str.swapcase() |
str.title() |
str.translate(table) |
str.upper() |
str.zfill(width) | 

### printf-style String Formatting

one sample,
```
>>> print('%(language)s has %(number)03d quote types.' %
...       {'language': "Python", "number": 2})
Python has 002 quote types.
```

conversion flag | note
---|---
'#' | The value conversion will use the “alternate form”
'0' | zero padding
'-' | left adjusted
' ' | A blank should be left before a positive number (or empty string) produced by a signed conversion.
'+' | a sign character precede.

conversion type | note
---|---
d i u | signed integer decimal
o | signed octal value
u | same as d
x X |
e E |
f F | 
g G |
c | single char
r | string repr()
s | string str()
a | string ascii()
% | no argument is converted.

## Binary sequence types: bytes, bytearray, memoryview
---

### bytes object
bytes object is immutable  sequences of single bytes.

class bytes([source[, encoding[,errors]]])

### bytearray object
bytearray object is mutable counterpart to bytes object.

### Memory views
memoryview objects allow Python code to access the internal data of an object that supports the buffer protocol without copying.


## Set Types: set, frozenset
---
A set object is an unordered collection of distinct hashable objects.  
There are currently two built-in set types, set and frozenset. The set type is mutable.  the contents can be changed using methods like add() and remove(). The frozenset type is immutable and hashable.  
```
class set([iterable]) 
class frozenset([iterable]) 
```
common opertaions | note
---|---
len(s) |
x in s |
x not in s |
isdisjoint(other) | 
issubset(other) or set <= other |
set < other |
issuperset(other) or set >= other |
set > other |
union(*others) or set \| other \| ... |
intersection(*others) or set & other & ... |
difference(*other) or set-other-... |
symmetric_difference(other) or set^other |
copy() |

opertion only for set | note
---|---
update(*others) or set \|= other \| ... |
intersection_update(*others) or set &= other &... |
difference_update(*others) or set -= other\|... |
symmetric_difference_update(other) or set ^= other |
add(elem) |
remove(elem) |
discard(elem) |
pop() |
clear() |


## Mapping Types: dict
---
A mapping object maps hashable values to arbitrary objects. Mappings are mutable objects.  
There is currently only one standard mapping type, the dictionary.

operation | note
---|---
len(d) |
d[key] |
d[key] = value |
del d[key] |
key in d |
key not in d |
iter(d) | return an iterator over the keys of the dictionary.
clear() |
copy() |
classmethod fromkeys(seq[,value]) |
get(key[,default]) |
keys() |
pop(key[,default]) |
popitem() |
setdefault(key[,default]) |
update([other]) |
values() |


### dictionary view objects
dict.keys(), dict.values()和dict.items()返回的就是view object. view object支持的函数，
func | note
---|---
len(dictview) |
iter(dictview) |
x in dictview | 

## Context Manager Types
---
'with' statement supports the concept of a runtime context defined by a context manager.

method | note
---|---
contextmanager.\_\_enter\_\_() |
contextmanager.\_\_exit\_\_() |

## Other built-in types
---
### module
two attributes: name and \_\_dict\_\_.
### function
The only operation on a function object is to call func(arg-list).
### method
Bound methods have two special read-only attributes: \_\_self\_\_ and \_\_func\_\_.  
Calling m(arg-1,arg-2,..,arg-n) is completely equivalent to calling m.\_\_func\_\_(m.\_\_self\_\_, arg-1, arg-2,..., arg-n).  
### code object
code object is returned by the built-in compile() function and can be extracted from function objects through their __code__ attribute.
### type object
Type object represents the various object types. an object type is accessed by the built-in function type().
### Null object
### Ellipsis object
### NotImplemented object
### Boolean value

## Special Attributes
---

attribute|note
---|---
object.\_\_dict\_\_ | used to store an object's(writable) attributes.
instance.\_\_class\_\_ | The class to which a class instance belongs.
class.\_\_bases\_\_ | the tuple of base classes of a class object
def.\_\_name\_\_ | the name of the class, function, method, descriptor, or generator instance
def.\_\_qualname\_\_ | the qualified name of the class, function, method, descriptor, or generator instance
class.\_\_mro\_\_ | This attribute is a tuple of classes that are considered when looking for base classes during method resolution.
class.mro() |
class.\_\_subclasses\_\_ |


# Built-in Exceptions

## Base exceptions
---
exceptions | note
---|---
BaseException | the base class for all built-in exceptions.
Exception | all built-in, non-system-exiting exceptions are derived from this class.
ArithmeticError | 
BufferError |
LookupError |

## Concrete exceptions
```
BaseException
 +-- SystemExit
 +-- KeyboardInterrupt
 +-- GeneratorExit
 +-- Exception
      +-- StopIteration
      +-- StopAsyncIteration
      +-- ArithmeticError
      |    +-- FloatingPointError
      |    +-- OverflowError
      |    +-- ZeroDivisionError
      +-- AssertionError
      +-- AttributeError
      +-- BufferError
      +-- EOFError
      +-- ImportError
           +-- ModuleNotFoundError
      +-- LookupError
      |    +-- IndexError
      |    +-- KeyError
      +-- MemoryError
      +-- NameError
      |    +-- UnboundLocalError
      +-- OSError
      |    +-- BlockingIOError
      |    +-- ChildProcessError
      |    +-- ConnectionError
      |    |    +-- BrokenPipeError
      |    |    +-- ConnectionAbortedError
      |    |    +-- ConnectionRefusedError
      |    |    +-- ConnectionResetError
      |    +-- FileExistsError
      |    +-- FileNotFoundError
      |    +-- InterruptedError
      |    +-- IsADirectoryError
      |    +-- NotADirectoryError
      |    +-- PermissionError
      |    +-- ProcessLookupError
      |    +-- TimeoutError
      +-- ReferenceError
      +-- RuntimeError
      |    +-- NotImplementedError
      |    +-- RecursionError
      +-- SyntaxError
      |    +-- IndentationError
      |         +-- TabError
      +-- SystemError
      +-- TypeError
      +-- ValueError
      |    +-- UnicodeError
      |         +-- UnicodeDecodeError
      |         +-- UnicodeEncodeError
      |         +-- UnicodeTranslateError
      +-- Warning
           +-- DeprecationWarning
           +-- PendingDeprecationWarning
           +-- RuntimeWarning
           +-- SyntaxWarning
           +-- UserWarning
           +-- FutureWarning
           +-- ImportWarning
           +-- UnicodeWarning
           +-- BytesWarning
           +-- ResourceWarning

```

# Text Processing Services
## string
---
### format string syntax

__replacement_field ::=  "{" [field_name] ["!" conversion] [":" format_spec] "}"__

```
"First, thou shalt count to {0}"  # References first positional argument
"Bring me a {}"                   # Implicitly references the first positional argument
"From {} to {}"                   # Same as "From {0} to {1}"
"My quest is {name}"              # References keyword argument 'name'
"Weight in tons {0.weight}"       # 'weight' attribute of first positional arg
"Units destroyed: {players[0]}"   # First element of keyword argument 'players'.

"Harold's a clever {0!s}"        # Calls str() on the argument first
"Bring out the holy {name!r}"    # Calls repr() on the argument first
"More {!a}"                      # Calls ascii() on the argument first
```

Accessing by position.
```
>>> '{0}, {1}, {2}'.format('a', 'b', 'c')
'a, b, c'
>>> '{}, {}, {}'.format('a', 'b', 'c')  # 3.1+ only
'a, b, c'
>>> '{2}, {1}, {0}'.format('a', 'b', 'c')
'c, b, a'
>>> '{2}, {1}, {0}'.format(*'abc')      # unpacking argument sequence
'c, b, a'
>>> '{0}{1}{0}'.format('abra', 'cad')   # arguments' indices can be repeated
'abracadabra'
```

Accessing by name.
```
>>> 'Coordinates: {latitude}, {longitude}'.format(latitude='37.24N', longitude='-115.81W')
'Coordinates: 37.24N, -115.81W'
>>> coord = {'latitude': '37.24N', 'longitude': '-115.81W'}
>>> 'Coordinates: {latitude}, {longitude}'.format(**coord)
'Coordinates: 37.24N, -115.81W'
```

Accessing attributes and items.
```
>>> c = 3-5j
>>> ('The complex number {0} is formed from the real part {0.real} '
...  'and the imaginary part {0.imag}.').format(c)
'The complex number (3-5j) is formed from the real part 3.0 and the imaginary part -5.0.'


>>> coord = (3, 5)
>>> 'X: {0[0]};  Y: {0[1]}'.format(coord)
'X: 3;  Y: 5'
```

str and repr
```
>>> "repr() shows quotes: {!r}; str() doesn't: {!s}".format('test1', 'test2')
"repr() shows quotes: 'test1'; str() doesn't: test2"
```

Aligning the text and specifying a width.
```
>>> '{:<30}'.format('left aligned')
'left aligned                  '
>>> '{:>30}'.format('right aligned')
'                 right aligned'
>>> '{:^30}'.format('centered')
'           centered           '
>>> '{:*^30}'.format('centered')  # use '*' as a fill char
'***********centered***********'
```

sign
```
>>> '{:+f}; {:+f}'.format(3.14, -3.14)  # show it always
'+3.140000; -3.140000'
>>> '{: f}; {: f}'.format(3.14, -3.14)  # show a space for positive numbers
' 3.140000; -3.140000'
>>> '{:-f}; {:-f}'.format(3.14, -3.14)  # show only the minus -- same as '{:f}; {:f}'
'3.140000; -3.140000'
```

base
```
>>> # format also supports binary numbers
>>> "int: {0:d};  hex: {0:x};  oct: {0:o};  bin: {0:b}".format(42)
'int: 42;  hex: 2a;  oct: 52;  bin: 101010'
>>> # with 0x, 0o, or 0b as prefix:
>>> "int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}".format(42)
'int: 42;  hex: 0x2a;  oct: 0o52;  bin: 0b101010'
```

Using the comma as a thousands separator:
```
>>> '{:,}'.format(1234567890)
'1,234,567,890'
```

a percentage
```
>>> points = 19
>>> total = 22
>>> 'Correct answers: {:.2%}'.format(points/total)
'Correct answers: 86.36%'
```

Using type-specific formatting:
```
>>> import datetime
>>> d = datetime.datetime(2010, 7, 4, 12, 15, 58)
>>> '{:%Y-%m-%d %H:%M:%S}'.format(d)
'2010-07-04 12:15:58'
```

>>> for align, text in zip('<^>', ['left', 'center', 'right']):
...     '{0:{fill}{align}16}'.format(text, fill=align, align=align)
...
'left<<<<<<<<<<<<'
'^^^^^center^^^^^'
'>>>>>>>>>>>right'
>>>
>>> octets = [192, 168, 0, 1]
>>> '{:02X}{:02X}{:02X}{:02X}'.format(*octets)
'C0A80001'

### template strings
Template support $-based substitutions,
* $$ is an escape
* $identifier is a substitution
* ${identifier} is equivalent to $identifier.

Template class implements above rules.


## re, Regular expression 
---
Unicode strings and 8-bit strings cannot be mixed.

### regular expression syntax

special char | note
---|---
. | matche any character except a newline.
^ | Matche the start of the string, and in MULTILINE mode also matche immediately after each newline
$ | Matche the end of the string or just before the newline at the end of the string, and in MULTILINE mode also matche before a newline. 
* |  0 or more repetitions of the preceding RE.
+ |  match 1 or more repetitions of the preceding RE
? |  match 0 or 1 repetitions of the preceding RE.
*?, +?, ?? | non-greedy or minimal fashion.
{m} |  exactly m repetitions
{m,n} | match from m to n repetitions of the preceding RE
{m,n}? | non-greedy
\ | 
[] | a set of characters
\| | or
(...) | Matches whatever regular expression is inside the parentheses, and indicates the start and end of a group; the contents of a group can be retrieved after a match has been performed, and can be matched later in the string with the \number special sequence
(?...) |
(?aiLmsux) | 
(?:...) |
(?imsx-imsx:...) |
(?P<name>...) | 
(?P=name) | a abckreference to a named group
(?#...) | a comment
(?=...) | lookahead assertion
(?!...) | 
(?<=...>) | preceded by a match
(?<!...>) | not preceded
(?(id/name)yes-pattern|no-pattern) |

\\sequence | note
---|---
\A | match only the start of string
\b | Matches the empty string, but only at the beginning or end of a word. 
\B | Matches the empty string, but only when it is not at the beginning or end of a word. 
\d | decimal digit
\D | Matches any character which is not a decimal digit.
\s | whitespace char
\S | not whitespace char
\w | alphanumeric in ascii or word in unicode
\W |
\Z | Matches only at the end of the string. 

### re functions

func | note
---|---
re.compile(pattern, flags=0) |
re.search(pattern,string,flags=0) | 注意与match()的区别。match是从字串的开头匹配。
re.match(pattern,string, flags=0) |
re.fullmatch(pattern,string,flags=0) | 
re.split(pattern,string,maxsplit=0, flags=0) | 
re.findall(pattern,string,flags=0) | 
re.finditer(pattern,string,flags=0) | 
re.sub(pattern,repl,string,count=0,flags=0) |
re.subn(pattern,repl,string,count=0,flags=0) |
re.escape(pattern) |
re.purge() |


### regular expression objects
Compiled regular expression objects support the following methods and attributes,

method | note
---|---
regex.search() |
regex.match() |
regex.fullmatch() |
regex.split() |
regex.findall() |
regex.finditer() |
regex.sub() |
regex.subn() |
regex.flags |
regex.groups |
regex.groupindex |
regex.pattern |

### match object

Match objects always have a boolean value of True. Since match() and search() return None when there is no match, you can test whether there was a match with a simple if statement:
```
match = re.search(pattern, string)
if match:
    process(match)
```

method&attribute |note
---|---
match.expand() |
match.group() |
match.\_\_getitem\_\_() |
match.groups() | Return a tuple containing all the subgroups of the match, from 1 up to however many groups are in the pattern. 
match.groupdict() | Return a dictionary containing all the named subgroups of the match, keyed by the subgroup name. 
match.start() |
match.end() |
match.span() |
match.pos() |
match.endpos() |
match.lastindex |
match.lastgroup |
match.re |
match.string |

一些例子，
```
>>> m = re.match(r"(?P<first_name>\w+) (?P<last_name>\w+)", "Malcolm Reynolds")
>>> m.group('first_name')
'Malcolm'
>>> m.group('last_name')
'Reynolds'

>>> m.group(1)
'Malcolm'
>>> m.group(2)
'Reynolds'

>>> m = re.match(r"(..)+", "a1b2c3")  # Matches 3 times.
>>> m.group(1)                        # Returns only the last match.
'c3'

>>> m = re.match(r"(\w+) (\w+)", "Isaac Newton, physicist")
>>> m[0]       # The entire match
'Isaac Newton'
>>> m[1]       # The first parenthesized subgroup.
'Isaac'
>>> m[2]       # The second parenthesized subgroup.
'Newton'

>>> m = re.match(r"(\d+)\.(\d+)", "24.1632")
>>> m.groups()
('24', '1632')

>>> m = re.match(r"(\d+)\.?(\d+)?", "24")
>>> m.groups()      # Second group defaults to None.
('24', None)
>>> m.groups('0')   # Now, the second group defaults to '0'.
('24', '0')

>>> m = re.match(r"(?P<first_name>\w+) (?P<last_name>\w+)", "Malcolm Reynolds")
>>> m.groupdict()
{'first_name': 'Malcolm', 'last_name': 'Reynolds'}

```

## difflib, Helpers for computing deltas
---
This module provides classes and functions for comparing sequences.

* class difflib.SequenceMatcher
* class difflib.Differ
* class difflib.HtmlDiff
* difflib.context_diff()
* difflib.get_close_matches()
* difflib.ndiff()
* difflib.restore()
* difflib.unified_diff()
* difflib.diff_bytes()

## textwrap, Text wrapping and filling
---

* textwrap.wrap()
* textwrap.fill()
* textwrap.shorten()
* textwrap.dedent()
* textwrap.indent()
* class textwrap.TextWrapper()

## unicodedata, Unicode Database
---
This module provides access to the Unicode Character Database (UCD) which defines character properties for all Unicode characters. The data contained in this database is compiled from the UCD version 9.0.0.

## stringprep, Internet String Preparation
---

## readline, GNU readline interface
---
### Init file
* readline.parse_and_bind()
* readline_init_file()

### Line buffer
* readline.get_line_buffer()
* readline.insert_text()
* redisplay()

### History file

### History list

### Startup hooks
### Completion

# Binary Data Services
## struct, Interpret bytes as packed binary data
---
This module performs conversions between Python values and C structs represented as Python bytes objects. This can be used in handling binary data stored in files or from network connections, among other sources.  

### functions

* struct.pack()
* struct.pack_into()
* struct.unpack()
* struct.unpack_from()
* struct.iter_unpack()
* struct.calcsize()

### Format strings

char | byte order | size | alignment
---|---|---|---
@ | native |native |
= | native | standard | none
< | little-endian | standard | none
> | big-endian | standard | none
! | network(BE) | standard | none

use 'sys.byteorder' to check the endianness.

format | C type | python type| standard size
---|---|---|---
x | pad byte | no value| 
c | char | bytes of length 1 | 1
b | signed char | integer | 1
B | unsigned char | integer | 1
? | _Bool | bool | 1
h | short | integer | 2
H | unsigned short | integer | 2
i | int | integer | 4
I | unsigned int | integer | 4
l | long | integer | 4
L | unsigned long | integer | 4
q | long long | integer | 8
Q | unsigned long long | integer | 8
n | ssize_t | integer
N | size_t | integer
e | | float | 2
f | float | float | 4
d | double | float | 8
s | char[] | bytes |
p | char[] | bytes |
P | void* | integer |

## codecs, Codec registry and base classes
---
This module defines base classes for standard Python codecs (encoders and decoders) and provides access to the internal Python codec registry, which manages the codec and error handling lookup process.   


# Data Types
## datetime, Basic date and time types
---
The datetime module supplies classes for manipulating dates and times in both simple and complex ways. There are two kinds of date and time objects, __naive__ and __aware__.  

### Available types
* class datetime.date
* class datetime.time
* class datetime.datetime
* class datetime.timedelta
* class datetime.tzinfo
* class datetime.timezone

Subclass relationships:
```
object
    timedelta
    tzinfo
        timezone
    time
    date
        datetime
```
### strftime() and strptime() 
## calendar, General calendar-related functions
---
This module allows you to output calendars like the Unix cal program, and provides additional useful functions related to the calendar.

## collections, Container datatypes
---
This module implements specialized container datatypes providing alternatives to Python's general purpose built-in containers, dict, list, set, and tuple.  

### ChainMap
### Counter
### deque
Deques are a generalization of stacks and queues.Deques support thread-safe, memory efficient appends and pops from either side of the deque with approximately the same O(1) performance in either direction.
### defaultdict
### namedtuple()
Named tuples assign meaning to each position in a tuple and allow for more readable, self-documenting code.
### OrderedDict
Ordered dictionaries are just like regular dictionaries but they remember the order that items were inserted. When iterating over an ordered dictionary, the items are returned in the order their keys were first added.

### UserDict
### UserList
### UserString

## collections.abc, Abstrace Base Classes for Containers
---
### heapq, Heap queue algorithm
## bisect, Array bisection algorithm
---
## array, Efficient arrays of numeric values
---
## weakref, Weak references
---
A weak reference to an object is not enough to keep the object alive: when the only remaining references to a referent are weak references, garbage collection is free to destroy the referent and reuse its memory for something else.   
A primary use for weak references is to implement caches or mappings holding large objects, where it抯 desired that a large object not be kept alive solely because it appears in a cache or mapping.  
Several built-in types such as list and dict do not directly support weak references but can add support through subclassing.  
Other built-in types such as tuple and int do not support weak references even when subclassed   

## types, Dynamic type creation and names for built-in types
---
This module defines utility function to assist in dynamic creation of new types.

## copy, Shallow and deep copy operations
---

## pprint, Data pretty printer
---
The formatted representation keeps objects on a single line if it can, and breaks them onto multiple lines if they don抰 fit within the allowed width. Construct PrettyPrinter objects explicitly if you need to adjust the width constraint.

## reprlib, Alternate repr() implementation
---
The reprlib module provides a means for producing object representations with limits on the size of the resulting strings. This is used in the Python debugger and may be useful in other contexts as well.

## enum, Support for enumerations
---
An enumeration is a set of symbolic names (members) bound to unique, constant values. Within an enumeration, the members can be compared by identity, and the enumeration itself can be iterated over.

# Numeric and Mathematical Modules
## numbers, Numeric abstract base classes
---

## math, Mathematical functions
---

### Number-theoretic and representation functions
func | note
---|---
ceil(x) | Return the ceiling of x, the smallest integer greater than or equal to x.
copysign(x,y) | Return a float with the magnitude (absolute value) of x but the sign of y
fabs(x) | Return the absolute value of x.
factorial(x) | Return x factorial. 
floor(x) | Return the floor of x, the largest integer less than or equal to x. 
fmod(x, y) | 
frexp(x) |
fsum(iterable) |
gcd(a,b) | Return the greatest common divisor of the integers a and b.
isclose(a, b, *, rel_tol=1e-09, abs_tol=0.0) | Return True if the values a and b are close to each other and False otherwise.
isfinite(x) | Return True if x is neither an infinity nor a NaN, and False otherwise.
isinf(x) | Return True if x is a positive or negative infinity,and False otherwise.
isnan(x) | Return True if x is a NaN (not a number), and False otherwise.
ldexp(x,i) | Return x * (2**i). 
modf(x) | Return the fractional and integer parts of x.
trunc(x) | Return the Real value x truncated to an Integral (usually an integer). 

### Power and logarithmic functions

func | note
---|---
exp(x) | e**x
expml(x) | e**x -1
log(x[,base]) | 
loglp(x) | natural logarithm of 1+x(base e)
log2(x) |
log10(x) |
pow(x,y) |
sqrt(x) |

### Trigonometric functions

func|note
---|---
acos(x) |
asin(x) |
atan(x) |
atan(y,x) |
cos(x) |
hypot(x,y) |
sin(x) |
tan(x) |

### Angular conversion

func | note
---|---
degrees(x) |
radians(x) |

### Hyperbolic functions

func | note
---|---
acosh() |
asinh() |
atanh() |
cosh() |
sinh() |
tanh() |

### Special functions

### Constants

const | note
---|---
pi |
e |
tau |
inf |
nan |

## cmath, Mathemetical functions for complex numbers
---
## decimal, Decimal fixed point and floating point arithmetic
---
## fractions, Rational numbers
---
## random, Generate pseudo-random numbers
---
### Bookkeeping functions
* seed()
* getstate()
* setstate()
* getrandbits()

### Functions for integers
* randrange()
* randint(a,b)

### Functions for sequences
* choice(seq)
* choices()
* shuffle()
* sample()

### Real-valued distributions

func | note
---|---
random | float in [0.0, 1.0)
uniform(a,b) | float in [a,b]
triangular() |
betavariate() |
expovariate() |
gammavariate() | 
gauss() |
lognormvariate() |
normalvariate() |
vonmisesvariate() |
paretovariate() |
weibullvariate() |

## statistics, Mathematical statistics functions
---
### averages and measures of central location
 func | note
 ---|---
 mean() |
 harmonic_mean() |
 median() | 
 median_low() |
 median_high() |
 median_grouped() |
 mode() |

 ### Measures of spread

 func | note
 ---|---
 pstdev() |
 pvariance() |
 stdev() |
 variance() |
 




# Functional Programming Modules
# File and Directory Access
# Data Persistence
# Data Compression and Archiving
# File Formats
# Cryptographic Services
# Generic Operating System Services
## argparse, Parser for command-line options, arguments and sub-commands
---
The argparse module makes it easy to write user-friendly command-line interfaces.  
argparse模块取代optparse模块.另一个常用的arg处理模块是getopt模块.

### ArgumentParser object


__class argparse.ArgumentParser(prog=None, usage=None, description=None, epilog=None, parents=[], formatter_class=argparse.HelpFormatter, prefix_chars='-', fromfile_prefix_chars=None, argument_default=None, conflict_handler='error', add_help=True, allow_abbrev=True)__

* prog - The name of the program (default: sys.argv[0]) 
* usage - The string describing the program usage (default: generated from arguments added to parser) 
* description - Text to display before the argument help (default: none) 
* epilog - Text to display after the argument help (default: none) 
* parents - A list of ArgumentParser objects whose arguments should also be included 
* formatter_class - A class for customizing the help output 
* prefix_chars - The set of characters that prefix optional arguments (default: '-') 
* fromfile_prefix_chars - The set of characters that prefix files from which additional arguments should be read (default: None) 
* argument_default - The global default value for arguments (default: None) 
* conflict_handler - The strategy for resolving conflicting optionals (usually unnecessary) 
* add_help - Add a -h/--help option to the parser (default: True) 
* allow_abbrev - Allows long options to be abbreviated if the abbreviation is unambiguous. (default: True) 

### The add_argument() method

__ArgumentParser.add_argument(name or flags...[, action][, nargs][, const][, default][, type][, choices][, required][, help][, metavar][, dest])__

* name or flags - Either a name or a list of option strings, e.g. foo or -f, --foo. 
* action - The basic type of action to be taken when this argument is encountered at the command line. 
* nargs - The number of command-line arguments that should be consumed. 
* const - A constant value required by some action and nargs selections. 
* default - The value produced if the argument is absent from the command line. 
* type - The type to which the command-line argument should be converted. 
* choices - A container of the allowable values for the argument. 
* required - Whether or not the command-line option may be omitted (optionals only). 
* help - A brief description of what the argument does. 
* metavar - A name for the argument in usage messages. 
* dest - The name of the attribute to be added to the object returned by parse_args(). 

### The parse_args() method

__ArgumentParser.parse_args(args=None, namespace=None)__


# Concurrent Execution
# Interprocess Communication and Networking
# Internet Data Handling
# Structured Markup Processing Tools
# Internet Protocols and Support
# Multimedia Services
# Internationalization
# Program Frameworks
# Graphical User Interface with Tk
# Development Tools
# Debugging and Profiling
# Software Packaging and Distribution
# Python Runtime Services
# Custom Python Interpreters
# Importing Modules
# Python Language Services
# Miscellaneous Services
# Ms Windows Specific Services
# Unix Specific Services
# Superseded Modules
# Undocumented Modules









# ref
* Mark Lutz, Programming Python 4th Edition.
* Mark Summerfield, Programming in Python 3 (Second Edition) A Complete Introduction to the Python Language.
* Mark Lutz, Learning Python, 5th Edition.
.Wesley J.Chun, Core PYTHON Applications Programming 3rd Edition.
* David Beazley, Python Cookbook 3rd Edition.




