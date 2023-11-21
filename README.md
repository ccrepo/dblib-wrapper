Project: DBlib-wrapper

Project DBlib-wrapper is a wrapper for database libs. This should allow plug and play for a variety for underlying DB libs.

The first supported DB lib will be sqlite (sqlite3).

This is also an exercise in how the C++ type system can be used to prohibit errors.

## Summary

DBlib-wrapper is implemented in C++. 

## Usage

1. Pre-requisites:

    Software:
    
    ```text
    Linux (Ubuntu 22.04.2 LTS (Jammy Jellyfish)).
    Gcc version 11.4.0.
    Gradle 8.0.2
    Sqlite3 3.37.0
    ```
    
2. Build:

    Navigate to project home directory and execute the following commands

    ```bash
    cd $projectDir
    ./gradlew clean
    ./gradlew build
    ```
    
    The build creates a shared lib located at $projectDir/lib/build/lib/main/debug/linux/

3. Helper Scripts

    There are helper scripts in the $projectDir/bin directory
    
    ```text
    projectDir/bin/c:  compile clean, build.
    projectDir/bin/r:  run test.
    ```
    
        
