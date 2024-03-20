#!/bin/bash

dst=./testlock

gcc -o $dst ./testlock.c
time $dst