clear all
clc  % clear console

% Our goal is a matrix with three columns and four rows
% We have sum of Cij and Xij, where i go to 4 and j go to 3, so our
% inverted O.F. looks like:
f = -[ 5000 4000 1800 5000 4000 1800 5000 4000 1800 5000 4000 1800];

% Next we must prepare our constraints, our equations without result (this
% number without "x"). It will be for Xij (i from 1 to 4, j from 1 to 3).
% For this purpose I'll create a matrix. In first row will be x11, x12, x13
% and rest of columns must be filled with zeros.
% Second row is for x21, x22, x23, but it's very important before x21 we
% have x11, x12, x13 and this three things will be filled by zereos.
% Third row looks like: 0 0 0 0 0 0 1 1 1, it means: x11, x12, ..., x31,
% x32, x33, and rest of columns will be zeros. For now A matrix looks like:
% [
%  x11, x12, x13, 0 0 0 0 0 0 0 0 0 (0 from x21 to x43)
%  0, 0, 0 (because x11, x12, x13) 1 1 1 0 0 0 0 0 0 (0 from x31 to x43)
%  0 0 0 0 0 0 (because x11, x12, x13, x21, x22, x23) 1 1 1 0 0 0
%  0 0 0 0 0 0 0 0 0 1 1 1
% After this in our A matrix we have equation: 
% 5.5Xi1 + 4Xi2 + 3.4Xi3 for i from 1 to 4, so there will be the same
% situation like before, next step our matrx looks like:
% 5.5 4 3.5 0 0 0 0 0 0 0 0 0 (0 from x21 to x43)
% 0 0 0 5.5 4 3.5 (because x11, x12, x13) 0 0 0 0 0 0 etc.
% Next we have Xij for i from 1 to 1 to 4 and j from 1 to 3.
% So finally our A matrix looks like: 
A = [1 1 1 0 0 0 0 0 0 0 0 0 
     0 0 0 1 1 1 0 0 0 0 0 0 
     0 0 0 0 0 0 1 1 1 0 0 0
     0 0 0 0 0 0 0 0 0 1 1 1
     5.5 4 3.5 0 0 0 0 0 0 0 0 0 
     0 0 0 5.5 4 3.5 0 0 0 0 0 0
     0 0 0 0 0 0 5.5 4 3.5 0 0 0 
     0 0 0 0 0 0 0 0 0 5.5 4 3.5
     1 0 0 1 0 0 1 0 0 1 0 0
     0 1 0 0 1 0 0 1 0 0 1 0
     0 0 1 0 0 1 0 0 1 0 0 1];
% In next step we must prepare vector where we can put the result our
% constraints. In the equation of our constrains you can see something like
% ≤ Di, ≤ Li and ≤ Rj, this variables are our result. We have 11 rows so
% we need 11 results of these equations.
b = [400; 650; 350; 500; 1800; 2200; 950; 1500; 660; 880; 400];
% In this step we must create next constraints, but in this case we have
% equality constraints. First is:
% (x11 + x12 + x13)/400 - (x21 + x22 + x23)/650 = 0, so first row looks
% like: 1/400 1/400 1/400 -1/650 -1/650 -1/650 0 0 0 0 0 0, these zeros
% means x31, x32, x33, x41, x42, x43. And we have next two rows...
Aq = [1/400 1/400 1/400 -1/650 -1/650 -1/650 0 0 0 0 0 0 
      1/400 1/400 1/400 0 0 0 -1/350 -1/350 -1/350 0 0 0
      1/400 1/400 1/400 0 0 0 0 0 0 -1/500 -1/500 -1/500];
bq = [0;0;0];  % it's for linear EQUALITY constraints. In this case we have
               % three equality constraints, which result is 0. Therefore 
               % this vector has three zeros.
lb = zeros(12,1);  % lower boundary 
ub = inf*ones(12,1);  % upper boundary. inf - because we don't have upper
                      % boundary in this case. 12, 1 - because out O.F. has
                      % 12 elements.
[x,fval] = linprog(f,A,b,Aq,bq,lb,ub);
fval = -fval  % because max(f) = -min(f)