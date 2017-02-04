#!/bin/bash

NAME=race

g++ -std=c++11 -DEVAL -Wall -o $NAME grader.cpp $NAME.cpp -lm
