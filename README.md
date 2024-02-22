# DuinoUtil
[TOC]
A collection of miscellaneous utility classes and functions.

## TimedActionSequence

Performs a sequence of actions with a time interval between each action.

## Util

The Util.h file provides a template function called LEN which returns the
number of elements in an array. So you can do the following:
```
int array[] = {1, 2, 3};
```
and `LEN(array)` will evaluate to `3`. The LEN template function will
generate a compiler error if passed a bare pointer rather than an array.
