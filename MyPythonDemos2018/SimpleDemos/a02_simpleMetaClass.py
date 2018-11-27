'''
    关于metaclass定义的基本语法
'''
import collections

class OrderedClass(type):

    @classmethod
    def __prepare__(metacls, name, bases, **kwds):
        print('OrderedClass::__prepare__')
        return collections.OrderedDict()

    def __new__(cls, name, bases, namespace, **kwds):
        print('OrderedClass::__new__()')
        print('cls =', cls, ' name=', name, ' namespace=', namespace)
        result = type.__new__(cls, name, bases, dict(namespace))
        result.members = tuple(namespace)
        return result

class A(metaclass=OrderedClass):
#class A():
    def __init__(self):
        print("A::__init__")

    def one(self): pass
    def two(self): pass
    def three(self): pass
    def four(self): pass

if __name__ == "__main__":
    print("create object.")
    a = A()
    print('A=', A)
    print('a=', a)
