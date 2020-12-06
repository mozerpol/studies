%%%%%%% FichaPL3_2 %%%%%%%
% objective function: max z = −3x1 + x2 − 4x3 + 3x4
% constraints: 
%  x1 + x2 + 3x3 + 2x4 ≤ 4
%  x1      -  x3 + x4  ≥ −1
% 2x1 + x2             ≤ 2
%  x1 + 2x2 + x3 + 2x4 = 2
%  x ≥ 0, i = 1,2,3,4

clf  % clear current figure, deletes from the current figure all graphics
     % objects
clear all  % delete all existing variables. all - is not a good habit

f = [3 -1 4 -3];  % our inverted O.F. Inverted because the o.f. is maximize
A = [1 1 3 2; -1 0 1 -1; 2 1 0 0];  % matrix with inequality constraints
Aq = [1 2 1 2];  % matrix with equality constraints
b = [4 ;1 ; 2];  % vector with results of our inequality constraints
bq = 2;   % vector with results of our equality constraints
lb = [0 0 0 0];  % lower boundry
ub = [inf inf inf inf];  % upper boundry

[x,fval] = linprog(f,A,b,Aq,bq,lb,ub);

maxAns = -fval