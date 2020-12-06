clf  % clear current figure, deletes from the current figure all graphics
     % objects
clear all  % delete all existing variables. all - is not a good habit

fb = [-2 -3 -1 -4 -3 -2 -2 -1 -3];  % our inverted O.F.
% matrix with inequality constraints, when the number is with minus sign it
% means that inequality is "≥" (like in the first line), otherwise it means
% that inequality inequality constraint is "≤" (like in the second line).
Ab = [0 -3 0 -1 -1 0 0 0 0
    1 1 0 0 0 0 0 0 0 
    0 1 0 1 -1 -1 0 0 0 
    0 -1 0 0 0 -2 -3 -1 -2
    0 0 -1 0 2 1 2 -2 1];
bb = [-3; 1; -1; -4; 5];  % vector with results of our equality constraints
Aqb = zeros(1,9);
bqb = 0;
lbb = zeros(9,1);  % lower binary boundary
ubb = ones(9,1);  % upper binary boundary
intconb = [1 2 3 4 5 6 7 8 9];


[xb,fvalb] = intlinprog(fb,intconb,Ab,bb,Aqb,bqb,lbb,ubb);
