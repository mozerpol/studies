clear all
clc

fa = [-2 -5];  % our inverted O.F. Inverted because the o.f. is maximize
% matrix with inequality constraints:
Aa = [10 30
     95 -30];
ba = [30; 75];  % vector with results of our inequality constraints
intcona = [1 2];  % x1 and x2 are binary, so we must give a sign about this
                  % fact intlinprog function. 1 and 2 means in this case, 
                  % that x1 and x2 will be binary vars.
Aqa = [0 0]; 
bqa = 0;

lba = zeros(2,1);  % lower boundry
uba = ones(2,1);  % upper boundry, because our vars are binary, so they can
                  % be only between 0 and 1

[xa,fvala] = intlinprog(fa,intcona,Aa,ba,Aqa,bqa,lba,uba);

maxAnsa = -fvala;