# -*- coding: utf8 -*-

class Student:
  def __init__(self, name, age) :
    self.name = name
    self.age = age
  def __eq__(self, other):
    return self.name == other.name
  def __add__(self, other):
    return self.name + other.name
  def __str__(self):
    return "Я оператор вывода! Меня зовут " + self.name 

a = Student("vasya", 14)
b = Student("petya", 13)
c = Student("vasya", 15)

print(a == b)
print(c == b)
print(a == c)
print(a + b)
print(a)
