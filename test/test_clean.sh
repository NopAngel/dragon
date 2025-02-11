#!/bin/bash
./Dragon .DragonC clean
if [ ! -f build/output ]; then
  echo "Clean test passed"
else
  echo "Clean test failed"
fi
