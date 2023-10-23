# InstaOrder

[![Windows Build](https://github.com/JerryAZR/InstaOrder/actions/workflows/windows-build.yml/badge.svg)](https://github.com/JerryAZR/InstaOrder/actions/workflows/windows-build.yml)

The project depends on openssl (and Qt6 if that isn't obvious). Without the dependencies compilation would fail.

easyssl is included as a submodule. Feel free to use any commit (or any fork if you have a preferred one).

Compiled binaries are not provided -- The **master** branch contains a public key (for authentication of course) that you might want to replace before compiling.
You are also free to change or event remove authentication completely.

I've added back the missing sources now that the popularity went down. That being said, There is no guarantee that the project compiles in your environment, so happy debugging XD.
