#!/bin/bash
case "$1" in
  "display") ;&
  "test")
        cd build
        make
        exitCode=$?
        if [ $exitCode -ne 0 ]; then
          echo 'make failed'
          exit $exitCode
        fi
        picotool load "$1.uf2"
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
      echo 'Invalid target'
esac
