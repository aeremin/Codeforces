import urllib.request
from html.parser import HTMLParser
import os.path

class CodeforcesParser(HTMLParser):
    def __init__(self):
        super(CodeforcesParser, self).__init__()
        self.openedDivs = []
        self.inputs = []
        self.outputs = []

    def handle_starttag(self, tag, attrs):
        if tag == 'div':
            self.openedDivs.append(attrs)
            if len(self.openedDivs) >= 2 and self.openedDivs[-2] == [('class', 'sample-test')]:
                if self.openedDivs[-1] == [('class', 'input')]:
                    self.inputs.append([])
                if self.openedDivs[-1] == [('class', 'output')]:
                    self.outputs.append([])

    def handle_endtag(self, tag):
        if tag == 'div':
            self.openedDivs.pop()

    def handle_data(self, data):
        if len(self.openedDivs) >= 2 and self.openedDivs[-2] == [('class', 'sample-test')]:
            data = data.replace(r'\n', '\n')
            if self.openedDivs[-1] == [('class', 'input')]:
                self.inputs[-1].append(data)
            if self.openedDivs[-1] == [('class', 'output')]:
                self.outputs[-1].append(data)

while True:
    problemUrl = input()
    if (problemUrl == ''):
        break
    
    pageContent=str(urllib.request.urlopen(problemUrl).read())

    parser = CodeforcesParser()
    parser.feed(pageContent)

    print(parser.inputs)
    print(parser.outputs)
    
    # Links supported
    # http://codeforces.com/contest/665/problem/C
    # http://codeforces.com/problemset/problem/663/A
    # http://codeforces.com/contest/1065/problem/C
    # http://codeforces.com/problemset/problem/1063/A

    splittedUrl = problemUrl.split('/')
    problemNumber = splittedUrl[-3]
    if problemNumber == 'problem':
        problemNumber = splittedUrl[-2]
    problemLetter = splittedUrl[-1]


    solverName = 'Solver' + problemNumber + problemLetter
    solverFilePath = '../../Solvers/' + problemNumber[:-2] + 'xx/' + problemNumber

    os.makedirs(solverFilePath, exist_ok=True)
    stubFile = open(os.path.join(solverFilePath, solverName + ".cpp"), "w")

    print('#include <Solvers/pch.h>',
          '#include "algo/io/baseio.hpp"',
          '#include "iter/range.h"',
          'using namespace std;',
          '',
          '// Solution for Codeforces problem http://codeforces.com/contest/%s/problem/%s' % (problemNumber, problemLetter),
          'class ' + solverName + ' {',
          'public:',
          '    void run();',
          '};',
          '',
          'void ' + solverName + '::run() {',
          '',
          '}',
          '',
          '',
          'class ' + solverName + 'Test : public ProblemTest {};',
          '',
          '',
          file=stubFile, sep = '\n')

    samplesCount = len(parser.inputs)
    for i in range(samplesCount):
        print('TEST_F(%sTest, Example%d) {' % (solverName, i + 1),
              '    setInput(R"(' +  '\n'.join(parser.inputs[i]),
              ')");',
              '    string output = R"(' + '\n'.join(parser.outputs[i]),
              ')";',
              '    %s().run();' % solverName,
              '    EXPECT_EQ_FUZZY(getOutput(), output);',
              '}',
			  '',
              file=stubFile, sep = '\n')


    cmakeLineToInsert = '    ${solvers_dir}/%s/%s/%s.cpp\n' % (problemNumber[:-2] + 'xx', problemNumber, solverName)
    cmakeFileName = os.path.join('..', '..', 'CMakeLists.txt')
    cmakeFile = open(cmakeFileName, 'r')
    cmakeLines = cmakeFile.readlines()
    cmakeFile.close()

    foundFileList = False
    for i in range(len(cmakeLines)):
        if cmakeLines[i] == cmakeLineToInsert:
            break
        if foundFileList and cmakeLines[i] > cmakeLineToInsert:
            cmakeLines.insert(i, cmakeLineToInsert)
            break
        if cmakeLines[i] == 'set(tests_srcs\n':
            foundFileList = True

    cmakeFile = open(cmakeFileName, 'w')
    cmakeFile.writelines(cmakeLines)
    cmakeFile.close()