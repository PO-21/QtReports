#!/bin/bash

sudo apt-get install gcc-4.8 g++-4.8 gcov-4.8 qt5-default qttools5-dev-tools
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8
sudo update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-4.8