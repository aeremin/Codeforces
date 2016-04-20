import urllib.request
from html.parser import HTMLParser
import os.path

problemUrl = "http://codeforces.com/contest/653/problem/A"
pageContent=str(urllib.request.urlopen(problemUrl).read())
#print(pageContent)

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
            if self.openedDivs[-1] == [('class', 'input')]:
                self.inputs[-1].append(data)
            if self.openedDivs[-1] == [('class', 'output')]:
                self.outputs[-1].append(data)

parser = CodeforcesParser()
parser.feed(pageContent)

print(parser.inputs)
print(parser.outputs)

splittedUrl = problemUrl.split('/')
problemNumber = splittedUrl[-3]
problemLetter = splittedUrl[-1]

solverName = 'Solver' + problemNumber + problemLetter
solverFilePath = '../../Solvers/' + problemNumber[0] + 'xx/' + problemNumber

try:
    os.mkdir(solverFilePath)
except Exception:
    pass

stubFile = open(os.path.join(solverFilePath, solverName + ".cpp"), "w")

print('#include <Solvers/pch.h>',
      '#include "algo/io/baseio.hpp"',
      '#include "iter/range.h"',
      'using namespace std;',
      '',
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
          '    string input = R"(' +  '\n'.join(parser.inputs[i]),
          ')";',
          '    string output = R"(' + '\n'.join(parser.outputs[i]),
          ')";',
          '    output.pop_back();',
          '    setInput(input);',
          '    %s().run();' % solverName,
          '    EXPECT_EQ(output, getOutput());',
          '}',
          file=stubFile, sep = '\n')
