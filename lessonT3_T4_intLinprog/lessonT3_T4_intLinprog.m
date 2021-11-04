%clear all
clc  % clear console
%%%%%%% intLinprog %%%%%%%
% For solving mixed-integer linear problems
% Example:
% objective function: max z = 9x1 + 5x2 + 6x3 + 4x4
% constraints: 
% 6x1 + 3x2 + 5x3 + 2x4 ≤ 10
%              x3 +  x4 ≤ 1
% x3 ≤ x1 and x4 ≤ x2
% xj is binary for j=1,2,3,4

A = [-9 -5 -6 -4];  % our inverted O.F.
b = [6 2 5 2; 0 0 1 1];  % constraints
f = [10; 1];  % result of our inequality constraints
Aqb = zeros(1,4);  % because we have four variables in O.F.
bqb = 0;  % because we don't use equations, only inequality constraints
lbb = zeros(4,1);  % because we have four variables in O.F.
ubb = ones(4,1);  % because we have four variables in O.F.
intcon = [1 2 3 4];  % it's pointer for our var, which vars are binary 
                     % intiger
[xb, fvalb] = intlinprog(A, intcon, b, f, Aqb, bqb, lbb, ubb);
% xb - solution  returned as a vector/matrix
% fvalb - objective value, returned as the scalar value (xb is matrix!)
