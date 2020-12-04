clf  % clear current figure, deletes from the current figure all graphics
     % objects
clear all  % delete all existing variables. all - is not a good habit
x1 = 0:1:15;
y = 0:1:15;
hold on  % retain current plot when adding new plots
plot(x1, 12-6/5*x1, 'r')  % plot(X,Y,LineSpec) LineSpec - line style  % jak ona zrobila to rownianie 12-6/5*x1
plot(x1, 7.5-1/2*x1, 'g')
line(8, y)
plot(x1, (1/450)*3375-(500/450)*x1, '--b')                          % jak ona znalazla te liczby 3k3...
plot(x1, (1/450)*4275-(500/450)*x1, '--b')
plot(x1, (1/450)*5080-(500/450)*x1, '--b')
hold off
grid on
axis([0 15 0 20])  % [range_for_x_axis range_for_y_axis]
xlabel('x_1')
ylabel('y_1')
title('Decision space')

%  second attempt, how to solve Ax = b equation
A = [6 5; 10 20]  % 6x1 + 5x2 = ... and 10x1 + 20x2 = ...                   % czemu 150, a nie 1500
B = [60 150]';  % ... = 60 and ... = 150. Matrix' - means matrix
                % transposition, thus in this case we can multiply A and B.
P = inv(A)*B  % inv - matrix inverse, the same as X^(-1)
figure(2)  % create new figure window
plot(P(1), P(2), 'ob')
text(6.4, 4.5, 'P')  % 6.4 and 5 is our approximate result


% czyli wychodzi na to, ze nie musimy uzywac simplexa, tylko to?
