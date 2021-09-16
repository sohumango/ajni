#!/usr/bin/env bash

JAVA_HOME=$(jrunscript -e 'java.lang.System.out.println(java.lang.System.getProperty("java.home"));' 2>/dev/null)

JNI1="$JAVA_HOME/include"
JNI2="$JNI1/darwin"
# echo $JNI1

gcc -O -fPIC -std=c++0x -I$JNI1 -I$JNI2 -I./ Sample.cpp -lstdc++ -shared -o libSample.dylib

javac com/test/Test.java com/test/StudentRecord.java

java -Djava.library.path=$(pwd) com.test.Test