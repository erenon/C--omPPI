#!/bin/bash

echo "Generate ODB entities"

for input in $@; do
    echo -n "check:" $input "... "
    
    if [ \
        ! -f "$(dirname $input)/gen/$(basename $input '.h')-odb.cxx" \
    -o  ! -f "$(dirname $input)/gen/$(basename $input '.h')-odb.hxx" \
    -o  ! -f "$(dirname $input)/gen/$(basename $input '.h')-odb.ixx" \
    -o  ! -f "$(dirname $input)/gen/$(basename $input '.h').sql" \
    \
    -o  $input -nt "$(dirname $input)/gen/$(basename $input '.h')-odb.cxx" \
    -o  $input -nt "$(dirname $input)/gen/$(basename $input '.h')-odb.hxx" \
    -o  $input -nt "$(dirname $input)/gen/$(basename $input '.h')-odb.ixx" \
    -o  $input -nt "$(dirname $input)/gen/$(basename $input '.h').sql" \
    ]; then
        echo "generate"
        
        odb -d mysql --std c++11 --generate-schema --generate-query \
        --guard-prefix COMPPI_ENTITY_GEN_ \
        --include-with-brackets --include-prefix comppi/entity/ \
        --include-regex "%comppi/entity/(.+)-odb(.+)%comppi/entity/gen/\1-odb\2%" \
        --output-dir $(dirname $input)/gen/ \
        -x -I"$(dirname $input)/../../" \
        $input
        
    else
        echo "nop"
    fi
done;
