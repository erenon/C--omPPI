#!/bin/bash

defaultBuild="Debug"
build=${1:-$defaultBuild}

bindir="$( cd "$( dirname "$0" )" && pwd )"
bin=$bindir"/../"$build"/comppi --root "$bindir"/../"

$bin build systemtype
$bin build map
$bin build interaction
$bin build localization

$bin generate namelookup
