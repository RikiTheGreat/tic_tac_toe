# TicTacToe Project

### Building
##### Go to the source directory
``
conan install . --output-folder=build --build=missing
``
##### Then
``
    cmake -Bbuild -H. && cd build && cmake --build .
``

#### Your game is waiting for you at ``build/src/`` directory
### Note !
    To play GPT-mode, Put your openai_key inside openai_api_key.txt.