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

needs_rebuild daysy daysy.c && $cc -o daysy daysy.c
