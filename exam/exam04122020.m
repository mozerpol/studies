clear all
clc  % clear console

f = -[12 6 18 8 6 3 18 16 3 1.5 9 8];  % objective function

A = [1 1 1 1 0 0 0 0 0 0 0 0 
     0 0 0 0 1 1 1 1 0 0 0 0
     0 0 0 0 0 0 0 0 1 1 1 1
     -1 -1 -1 -1 0 0 0 0 0 0 0 0 
     0 0 0 0 -1 -1 -1 -1 0 0 0 0
     0 0 0 0 0 0 0 0 -1 -1 -1 -1];

 b = [500; 1500; 700; 1000; -20; -10; -5];
 
Aq = [12 -6 0 0 0 -6 0 0 3 -3 0 0  % 1
      4 -2 0 0 0 -2 0 0 1 -1 0 0  % 2
      4 2 -18 0 0 0 -18 0 1 0 -9 0  %3
      12 6 0 -8 0 0 0 -16 3 0 0 -8];  %4
 
bq = [0;0;0];