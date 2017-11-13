#!/bin/bash

javac -cp ~/user/library/showme.jar source/visualize.java || exit 1
java -cp ~/user/library/showme.jar:source showme.framework.ShowMe --visualizer=visualize --gallery=tests-visual.html tests/ '??' || exit 1

