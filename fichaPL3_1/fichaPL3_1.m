% Example:
% objective function: min z = 0.4x1 + 0.5x2
% constraints: 
% 0.3x1 + 0.1x2 ≤ 2.7
% 0.6x1 + 0.4x2 ≥ 6
% 0.5x1 + 0.4x2 = 6
% x1 ≥ 0 and x1 ≥ 0

clear all
clc

f = [0.4 0.5]  % our OF
A = [0.3 0.1; -0.6 -0.4]  % inequality constraints
Aq = [0.5 0.5] % equality constraints
B = [2.7; -6]  % result of inequality constraints
bq = [6];  % result of equality constraints
lb = [0 0];  % because x1 ≥ 0 and x2 ≥ 0
ub = [inf inf];
% Select the algorithm for solver
options = optimoptions('linprog', 'Algorithm', 'dual-simplex');

[x, fval, exitflag, output] = linprog(f, A, B, Aq, bq, lb, ub, [], options)
sprintf('Min is %f', fval)