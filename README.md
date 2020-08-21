# FoxMath
Mathematical library coded in C++ in generic paradigme

Project run with C++ 2017 - 2020

c++ 2017 : g++ -std=gnu++17 -Werror -Wno-unknown-pragmas main.cpp -o exe && ./exe
c++ 2020 : g++ -std=gnu++2a -Werror -Wno-unknown-pragmas main.cpp -o exe && ./exe

## TODO:

- [x] GenericVector
- [x] Vector2, 3 and 4
- [x] strong_type implementation
- [x] Angle inherance of strong type
- [x] add angle to vector
- [ ] rework matrix
- [ ] add roate, translate and sclae function to generic vector
- [ ] add differente space unit like distance (meter, cm...), wigth (kg), volume...
- [ ] create floating point and integral unlimited type
- [ ] possibity to select random algorythm
- [ ] Create my own constexpr math library (sqrt, lerp.. is not constexpr on std). After that, rework class that uses them
- [ ] Make sur that likely optimization are on each condition
- [ ] Create benchmark feature and test all feature
- [ ] Dynamic Matrix, dynamic vector (without std::array)

## Readability
Program create on vscod with spaces of 4 for tabulation

Vscode extension use :
- Doxygen Documentation Generator by Christoph Schlosser
- Markdown Checkboxes by Matt Bierner
- TODO Highlight by Wayou Liu
- Snippet by vscode-snippet
- Resource Monitor by mutantdino

## License
MIT License

Copyright (c) 2020 Six Jonathan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
