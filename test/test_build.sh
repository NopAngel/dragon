#!/bin/bash
./Dragon .DragonC build
if [ -f build/output ]; then
  echo "Build test passed"
else
  echo "Build test failed"
fi
