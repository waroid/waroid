#!/bin/bash

gst-launch-1.0 -e rpicamsrc bitrate=1000000 preview=false ! video/x-h264,width=1280,height=720,framerate=25/1,profile=high ! h264parse ! rtph264pay config-interval=0 pt=96 ! gdppay ! tcpserversink host=0.0.0.0 port=5000

