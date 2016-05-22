find . -name '*.hpp' -printf '%p ' -or -name '*.cpp' -printf '%p ' | sed 's/\.\///g'
