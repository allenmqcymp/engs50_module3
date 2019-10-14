#!/bin/bash

find . -type f -perm +111 | grep "^./test" | xargs rm

