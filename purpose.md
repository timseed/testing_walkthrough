# Purpose

To try and show how testing/git/frameworks can be made to work together.

There are 4 branches in this project ...

  - master 
  - 1\_typical 
  - 2\_cmake\_build
  - 3\_cmake\_google\_tests


Master has our badly coded sqrt function. The function is total rubbish... we need to built automation around it... so we can try and find the error.

To get all the phases please do 

    git clone  https://github.com/timseed/testing_walkthrough
    cd testing_walkthrough

Now , we need to get all remote branches 

    git branch -r | grep -v '\->' | sed "s,\x1B\[[0-9;]*[a-zA-Z],,g" | while read remote; do git branch --track "${remote#origin/}" "$remote"; done

Let's check with

    git branch 
    
 We should see 4 branches 
 
``` 
  1_typical
  2_cmake_build
  3_cmake_google_tests
* master
```
