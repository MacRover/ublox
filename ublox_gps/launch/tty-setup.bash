#!/bin/bash
sudo tee /etc/udev/rules.d/usb-serial.rules > /dev/null <<EOF
SUBSYSTEM=="tty", ATTRS{idVendor}=="0403", ATTRS{idProduct}=="6015", MODE="0666", SYMLINK+="ttyMovingBase"
SUBSYSTEM=="tty", ATTRS{idVendor}=="1546", ATTRS{idProduct}=="01a9", MODE="0666", SYMLINK+="ttyRover"
EOF

sudo udevadm control --reload-rules
sudo udevadm trigger

echo it worked