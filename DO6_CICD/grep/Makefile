SHELL := /bin/bash
FLAG =-std=c11 -Wall -Wextra -Werror
FILE=revizor.txt revizor2.txt
PATTERNS=textpattern.txt

all: s21_grep tests
s21_grep: clean
	gcc $(FLAG) s21_grep.c -o s21_grep

tests:
	-diff <(./s21_grep Highlander $(FILE)) <(grep Highlander $(FILE))
	-diff <(./s21_grep -v Highlander $(FILE)) <(grep -v Highlander $(FILE))
	-diff <(./s21_grep -i Highlander $(FILE)) <(grep -i Highlander $(FILE))
	-diff <(./s21_grep -iv Highlander $(FILE)) <(grep -iv Highlander $(FILE))
	-diff <(./s21_grep -in Highlander $(FILE)) <(grep -in Highlander $(FILE))
	-diff <(./s21_grep -in Highlander $(FILE)) <(grep -in Highlander $(FILE))
	-diff <(./s21_grep -ie "^highlander" $(FILE)) <(grep -ie "^highlander" $(FILE))
	-diff <(./s21_grep -ince "^highlander" $(FILE)) <(grep -ince "^highlander" $(FILE))
	-diff <(./s21_grep -lh lan $(FILE)) <(grep -lh lan $(FILE))
	-diff <(./s21_grep -hc g $(FILE)) <(grep -hc g $(FILE))
	-diff <(./s21_grep -e Highlander -e highlander $(FILE)) <(grep -e Highlander -e highlander $(FILE))
	-diff <(./s21_grep -f $(PATTERNS) $(FILE)) <(grep -f $(PATTERNS) $(FILE))
	-diff <(./s21_grep -oi highlander $(FILE)) <(grep -oi highlander $(FILE))
	-diff <(./s21_grep -ohf $(PATTERNS) $(FILE)) <(grep -ohf $(PATTERNS) $(FILE))
	-diff <(./s21_grep -oinc highlander $(FILE)) <(grep -oinc highlander $(FILE))
	-diff <(./s21_grep -oihlnc -e highlander -e Lan -f textpattern.txt $(FILE)) <(grep -oihlnc -e highlander -e Lan -f textpattern.txt $(FILE))

clean: 
	rm -f s21_grep
