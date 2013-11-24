#!/bin/bash

# TODO generate uncommented fkeys:
# --fkeys-deferrable-mode not_deferrable <- unrecognized switch

# TODO review odb options (e.g: --omit-*)

if [ $# -lt 1 ]; then
    echo "Usage: $0 entity1.h [entity2.h [...]]"
    exit
fi

echo "Generate ODB entities"

bindir="$( cd "$( dirname "$0" )" && pwd )"

changed=false

for input in $@; do
    echo -n "check:" $input "... "
    
    if [ \
        ! -f "$(dirname $input)/gen/$(basename $input '.h')-odb.cxx" \
    -o  ! -f "$(dirname $input)/gen/$(basename $input '.h')-odb.hxx" \
    -o  ! -f "$(dirname $input)/gen/$(basename $input '.h')-odb.ixx" \
    \
    -o  $input -nt "$(dirname $input)/gen/$(basename $input '.h')-odb.cxx" \
    -o  $input -nt "$(dirname $input)/gen/$(basename $input '.h')-odb.hxx" \
    -o  $input -nt "$(dirname $input)/gen/$(basename $input '.h')-odb.ixx" \
    ]; then
        echo "generate"
        
        $changed = true
        
        odb -d mysql --std c++11 \
        --generate-query \
        --generate-prepared \
        --guard-prefix COMPPI_ENTITY_GEN_ \
        --include-with-brackets \
        --include-prefix comppi/entity/ \
        --include-regex "%comppi/entity/(.+)-odb(.+)%comppi/entity/gen/\1-odb\2%" \
        --output-dir $(dirname $input)/gen/ \
        -x -I"$(dirname $input)/../../" \
        $input
        
    else
        echo "nop"
    fi
done;

if [ $changed ]; then
    odb -d mysql --std c++11 \
    --generate-schema-only --at-once \
    -x -I$bindir"/../src/" \
    --output-name comppi \
    --output-dir $bindir \
    $@
fi
