#!/bin/bash

export QT_MESSAGE_PATTERN="[%{time yyyyMMdd h:mm:ss} %{if-debug}D%{endif}%{if-info}I%{endif}%{if-warning}W%{endif}%{if-critical}C%{endif}%{if-fatal}F%{endif}] %{file}:%{line}:%{category} - %{message}"
