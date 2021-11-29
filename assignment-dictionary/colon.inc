%define NEXT_ELEMENT 0
%macro colon 2
	%ifid %2
		%2: dq NEXT_ELEMENT
		%define NEXT_NODE %2
	%else
		%fatal "В аргументе 2 нужен идентификатор!"
	%endif
	%ifstr %1
		db %1, 0
	%else
		%fatal "В аргументе 1 ошибка!"
	%endif
%endmacro