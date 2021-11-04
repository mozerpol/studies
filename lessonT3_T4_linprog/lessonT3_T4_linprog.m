% Optimization Toolbox provides functions for finding parameters that
% minimize or maximize objectives like: linprog, intlinprog, quadprog, etc.
clear all
clc
%%%%%%% linprog %%%%%%%
% For solving LP problems
% Example:
% objective function: max z = 500x1 + 450x2
% constraints: 
% 6x1  + 5x2  ≤ 60
% 10x1 + 20x2 ≤ 150
% 8x2         ≤ 8       <- if we divide by 8 we can write: x1 ≤ 1
% x1 ≥ 0 and x2 ≥ 0

% At first we must invert objective function: max(f) = -min(f)
f = [-500 -450]  % our inverted OF
A = [6 5; 10 20; 1 0]  % [x1 x2 from first constraint; x1, x2; x1, x2]
B = [60 150 8]  % result of our inequality constraints
% Next we must choose the algorithm for solver
options = optimoptions('linprog', 'Algorithm', 'dual-simplex');
[x, fval, exitflag, output] = linprog(f, A, B, [], [], [], [], [], options)
sprintf('Max is %f', -fval)
% optimoptions - create optimization options,
% eg: options = optimoptions(SolverName)
% so... 
% optimoptions
% (
%   'linprog' - solver is a piece of mathematical software
%   'Algorithm' - which algorithm was used in this solver
%   'dual-simplex' - name of this algorithm
% )
% [ 
%   x - Solution, returned as a vector or array
%   fval - objective function value at the solution, returned as a number
%   exitflag - reason linprog stopped
%   output - information about the optimization process like iterations etc
% ]
% linprog - finds the MINIMUM, so if we have z max(f) we must do -min(f)
% (
%   f - coefficient vector represents the objective function
%   A - linear INEQUALITY constraints
%   B - linear INEQUALITY constraints
%   [] - linear EQUALITY constraints, if we don't have equality put []
%   [] - linear EQUALITY constraints
%   [] - lower bounds
%   [] - upper bounds
%   options - additional options
% )




