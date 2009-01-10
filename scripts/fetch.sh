#!/bin/sh

# Get cobject
[ -d vendor/cobject ] || hg clone http://projects.stoneship.org/hg/shared/cobject vendor/cobject

# Get uctest
[ -d vendor/uctest ] || hg clone http://projects.stoneship.org/hg/shared/uctest vendor/uctest
