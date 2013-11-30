#!/bin/bash

if [ $# -lt 3 ]; then
    echo "Usage: type driver-name field-count"
    echo "Available types: map, interaction, localization"
    exit 1
fi

bindir="$( cd "$( dirname "$0" )" && pwd )"
cd $bindir

type=$1
name=$2
fname=$(echo $2 | tr '[:lower:]' '[:upper:]')
fcount=$3

  sed s/__NAME__/$name/g < $type.h \
| sed s/__FCAPS_NAME__/$fname/g \
| sed s/__FIELD_COUNT__/$fcount/g \
> /var/tmp/$name.h

  sed s/__NAME__/$name/g < $type.cc \
| sed s/__FCAPS_NAME__/$fname/g \
| sed s/__FIELD_COUNT__/$fcount/g \
> /var/tmp/$name.cc
