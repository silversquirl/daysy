#!/bin/sh
# Who needs make?

cc="cc" # Change this if you want to use a different compiler

needs_rebuild() {
  [ -f "$1" ] || return 0
  tgt="$(stat -c %Y -- "$1")"
  shift
  for x; do
    [ "$(stat -c %Y -- "$x")" -gt "$tgt" ] && return 0
  done
  return 1
}

needs_rebuild daysy.o daysy.c daysy.h && $cc -c daysy.c
needs_rebuild libdaysy.a daysy.o && ar rcs libdaysy.a daysy.o
needs_rebuild libdaysy.so daysy.o && $cc -shared -o libdaysy.so daysy.o
needs_rebuild daysy main.c libdaysy.a daysy.h && $cc -o daysy main.c libdaysy.a
true
