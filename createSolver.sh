mkdir createSolverTmp
cd createSolverTmp

curl "http://codeforces.com/contest/${1}/problem/${2}" > problem.txt;

sed -e 's/<div/\n<div/g' -i problem.txt
sed -e 's/<\/div>/\n<\/div>/g' -i problem.txt
sed -e 's/<pre>/\n<pre>/g' -i problem.txt
cat problem.txt | grep '<div class="input">\|<div class="output">\|<pre>' > io.txt
sed -e 's/<pre>/R"(/g' -i io.txt
sed -e 's/<\/pre>/)";/g' -i io.txt
sed -e 's/<div class="input">/string input = /g' -i io.txt
sed -e 's/<div class="output">/string output = /g' -i io.txt
sed -e 'N;s/ = \n/ = /g' -i io.txt

solver="Solver${1}${2}"

printf "#include <Solvers/pch.h>\n" >> out.cpp
printf "#include \"algo/io/baseio.hpp\"\n" >> out.cpp
printf "#include \"algo/range.hpp\"\n" >> out.cpp
printf "using namespace std;\n\nclass ${solver}\n{\npublic:\n    void run();\n};\n\nvoid ${solver}::run()\n{\n\n}\n\n" >> out.cpp
printf "class ${solver}Test : public ProblemTest {};\n\n" >> out.cpp

exampleNumber=0

while read inputString; do
  read outputString;
  ((exampleNumber++));
  echo "TEST_F(${solver}Test, Example${exampleNumber})";
  echo '{';
  echo "    ${inputString}";
  echo "    ${outputString}";
  echo "    output.pop_back();"
  echo "    setInput(input);"
  echo "    ${solver}().run();";
  echo '    EXPECT_EQ(output, getOutput());';
  echo '}';
  echo '';
  echo '';
done <io.txt >>out.cpp

sed -e 's/<br \/>/\n/g' -i out.cpp

groupFolder=${1:0:1}
echo $groupFolder
mkdir "../Solvers/${groupFolder}xx"
mkdir "../Solvers/${groupFolder}xx/${1}"
cat out.cpp > "../Solvers/${groupFolder}xx/${1}/Solver${1}${2}.cpp"

cd ..
rm -rf createSolverTmp
