#!/bin/bash

cmake -E env CXXFLAGS="-DQT_NO_CAST_FROM_ASCII" cmake ..
