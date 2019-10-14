#!/bin/bash

$(find . -maxdepth 1 -executable -type f | grep '^./test' | xargs rm)
