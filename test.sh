#!/bin/bash

prog=$1
dir=$2

for file in $dir/*.in
do
  echo $file
  valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./$prog < $file 1> /dev/null 2> ${file%in}valout
  echo valgrind exitcode: $?

  ./$prog < $file 1> ${file%in}myout 2> ${file%in}myerr

  if diff ${file%in}out ${file%in}myout > /dev/null && diff ${file%in}err ${file%in}myerr > /dev/null
  then
    echo odpowiedzi - OK
  else
    echo odpowiedzi - ZLE
  fi
done
