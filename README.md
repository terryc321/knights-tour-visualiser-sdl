## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)
* [Usage](#usage)
* [Data format](#data-format)
* [Solutions](#solutions)


## General info
This project is a knights tour visualiser

The purpose was to get something up and running using SDL2 libraries.

It illustrates how good a de-coupled system can be.

For example the graphical interface may change , i may decide to use gtk , qt , kde , xlib or
wayland libraries as front end instead.

May decide to change the code generating program on the back end from scheme program to haskell , python , common lisp,
clojure , java or whatever.

the data generated will still be as relevant.

Also data can be used as a reference for a faster implementation.

able to write programs in multiple languages then the results should all be identical , this helps isolate a language
mistake from computation - example may be a rogue macro in lisp

able to write multiple front ends

as later move to transpilation where take scheme program and convert it to other languages , we are then decoupled from
that language if for any reason it went away temporarily

## Technologies
Project is created with:
* C code
* SDL2 libraries
	
## Setup
To run this project, install sdl2 libraries then run make :

```
$ make
```

## Usage
run the program with knights tour data file , an example file is
provided called small.txt , contains 1000 steps of a knights tour.

```
$ ./tour small.txt
```

## Data format
Knights tour data format is as simple as it gets , each line in the file
has three numbers.
First number refers to the nth-step of the knights tour , so first knight
placed on board would be a 1 .
The last knight placed on a board 8 x 8 completing the knights tour would be
 64 .
The next two numbers refer to the column and row .
so if my first move was to place my knight on bottom left square that would yield
 1 1 1
if i wanted my first move to be three columns in and five rows up , i would use
1 3 5
simples.


## Solutions
Knights tour is fairly simple to solve once realise if knight has blocked off
the corner square then it can never complete the knights tour.

How many solutions are there ?

How would be able to tell one solution from another?



