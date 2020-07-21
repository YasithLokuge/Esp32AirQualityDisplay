#!/bin/bash
# copied from https://codeblog.dotsandbrackets.com/gitlab-ci-esp32-arduino/
sudo apt-get update
cd ~

# Install arduino-cli
sudo apt-get install curl -y
curl -L -o arduino-cli.tar.bz2 https://downloads.arduino.cc/arduino-cli/arduino-cli-latest-linux64.tar.bz2
tar xjf arduino-cli.tar.bz2
rm arduino-cli.tar.bz2
sudo cp arduino-cli /usr/bin/

# Install python, pip and pyserial
sudo apt-get install python -y
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python get-pip.py
pip install pyserial

# Install esp32 core
printf "board_manager:\n  additional_urls:\n    - https://dl.espressif.com/dl/package_esp32_index.json\n" > .arduino-cli.yaml
arduino-cli core update-index --config-file .arduino-cli.yaml
arduino-cli core install esp32:esp32 --config-file .arduino-cli.yaml

# Install 'native' packages
arduino-cli lib install "Adafruit CCS811 Library"
arduino-cli lib install "lcdgfx"
cd -
