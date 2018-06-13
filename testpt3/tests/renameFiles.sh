#!/bin/bash

echo "RENAMING FILES <name_to_add>"

for f in *.in; do
  mv "${f}" "${1}${f}"
done

for f in *.out; do
  mv "${f}" "${1}${f}"
done

for f in *.err; do
  mv "${f}" "${1}${f}"
done
