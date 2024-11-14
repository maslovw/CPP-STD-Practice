#!/bin/bash
bazel test --test_output=all //test/permutations:partition
bazel test --test_output=all //test/heaps:heaps
