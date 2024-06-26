#!/bin/env bash
usage='
Description
  Builds and uploads binaries to the pi-pico board using picotool

Usage
  ./upload.sh life.test        build and upload the test binary to the pico using pictool 
  ./upload.sh pico-life   build and upload the pico-life binary to the pico using pictool'
case "$1" in
  "pico-life") ;&
  "life.test")
        cd build
        make
        exitCode=$?
        if [ $exitCode -ne 0 ]; then
          echo 'make failed'
          exit $exitCode
        fi
        picotool load -f "$1.uf2"
        exitCode=$?
        if [ $exitCode -ne 0 ]; then
          echo 'picotool load failed'
          exit $exitCode
        fi

        picotool reboot
        exitCode=$?
        if [ $exitCode -ne 0 ]; then
          echo 'picotool reboot failed'
          exit $exitCode
        fi
        ;;
    *)
      echo "$usage"
      exit 1
esac
