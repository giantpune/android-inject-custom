#!/bin/bash

set -e
set -x

ON_DEVICE="/data/logging"
LOCAL="bin"

adb push "$LOCAL/agent.so" "$ON_DEVICE"
adb push "$LOCAL/inject" "$ON_DEVICE"
adb shell chmod 0755 "$ON_DEVICE/inject"
adb shell chmod 0755 "$ON_DEVICE/agent.so"

SYSTEM_SERVER="$(adb shell ps | grep system_server | awk '{print $2}')"

adb shell "su -c 'cd $ON_DEVICE && $ON_DEVICE/inject $SYSTEM_SERVER'"
#adb shell "su -c '$ON_DEVICE/inject $SYSTEM_SERVER'"

