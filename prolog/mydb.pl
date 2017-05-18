
% Tutorials @ http://www.ic.unicamp.br/~meidanis/courses/mc336/2009s2/prolog/problemas/

% P08 (**) Eliminate consecutive duplicates of list elements.
% If a list contains repeated elements they should be replaced with a single copy of the element. The order of the elements should not be changed.
% 
% Example:
% ?- compress([a,a,a,a,b,c,c,a,a,d,e,e,e,e],X).
% X = [a,b,c,a,d,e]


ncompress([],[]).
ncompress([X],[X]).
ncompress([X,X|Xs], Zs) :- ncompress( [X|Xs], Zs).

mycompress([],[]).
mycompress([X,Y|T], Res) :- compress([Y|T],Res), X=:=Y, Res == [Y|Res];
      Res == [X,Y|R]. 


% P07 (**) Flatten a nested list structure.
% Transform a list, possibly holding lists as elements into a `flat' list by replacing each list with its elements (recursively).
% 
% Example:
% ?- my_flatten([a, [b, [c, d], e]], X).
% X = [a, b, c, d, e]
% 
% Hint: Use the predefined predicates is_list/1 and append/3


append(A, [], [A]).
append(A, [H|T], [H|S]) :- append(A, T, S). 

is_list([]).
is_list([_|T]) :- is_list(T).

flatten_list([], Result, Result).
flatten_list([H|T], X, Accumulator) :- 

  is_list(H), 
  flatten_list(H, XAccumulator, Accumulator),
  flatten_list(T, X, XAccumulator);

  append(H, Accumulator, Accumulator_appended), 
  flatten_list(T, X, Accumulator_appended).



%P06 (*) Find out whether a list is a palindrome.
%A palindrome can be read forward or backward; e.g. [x,a,m,a,x].

% [trace]  ?- palindrome([3,2,1,2,3]).      = true
% [trace]  ?- palindrome([3,2,0,1,2,0,2,3]) = false


compare_list([],[]).
compare_list([H1|T1],[H2|T2]) :- H1 =:= H2, compare_list(T1,T2).

palindrome(X) :- 
  reverse(X, Y, []),
  compare_list(X, Y).



%P05 (*) Reverse a list.
% This one was a bit tricky to understand
% Got a bit help from http://stackoverflow.com/questions/15070662/making-a-reverse-list
% An accumulator is sent as a parameter empty list []
%  1. call [1|_]
%  2. call [2 | 1]
%  3. call [3 | 2,1]
% Actual trace:
/*
[trace]  ?- reverse([1,2,3],R,[]).
   Call: (7) reverse([1, 2, 3], _G1603, []) ? creep
   Call: (8) reverse([2, 3], _G1603, [1]) ? creep
   Call: (9) reverse([3], _G1603, [2, 1]) ? creep
   Call: (10) reverse([], _G1603, [3, 2, 1]) ? creep
   Exit: (10) reverse([], [3, 2, 1], [3, 2, 1]) ? creep
   Exit: (9) reverse([3], [3, 2, 1], [2, 1]) ? creep
   Exit: (8) reverse([2, 3], [3, 2, 1], [1]) ? creep
   Exit: (7) reverse([1, 2, 3], [3, 2, 1], []) ? creep
R = [3, 2, 1].
*/
% ?- reverse([1,2,3], Reversed, []).

reverse([], Reversed, Reversed).
reverse([H|T], Reversed, Accu) :- reverse(T, Reversed, [H|Accu]).


%P04 (*) Find the number of elements of a list.
%shell => length([1,2,3,3,4,5,6,7],L).
%         L=8

array_length([],_).
array_length([_|T], L) :- array_length(T,L), L is (L + 1).

%P03 (*) Find the K'th element of a list.
%The first element in the list is number 1.
%Example:
%?- element_at(X,[a,b,c,d,e],3).
%X = c

element_at(1,[H|_], H).
element_at(K,[_|T],X) :- I is (K-1), element_at(I,T,X).


%P02 (*) Find the last but one element of a list.
%(zweitletztes Element, l'avant-dernier élément)

my_secondlast([X,_|[]], X).
my_secondlast([_|T],R) :- my_secondlast(T,R).


%P01 (*) Find the last element of a list.
%Example:
%?- my_last(X,[a,b,c,d]).
%X = d
my_last([R|[]], R).
my_last([_|T], R) :- my_last(T, R).

