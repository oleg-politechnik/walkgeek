#!/bin/sh

find . -name '*.mp3' -o -name '*.wav' -o -name '*.opus' | sort >> index.txt
