raspivid -t 0 -w 1280 -h 720 -fps 30 -b 2000000 -n -o - | ./test-launch "( fdsrc ! h264parse ! rtph264pay name=pay0 pt=96 )"
