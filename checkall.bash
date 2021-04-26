#!/bin/bash

_value=""
_test_file=""
_project_file=""
_m_output=""
projectName="./Project04"
_valgrindFile=""


# valgrind  --leak-check=full --log-file="_valgrind_3.txt" ./Project04 input_3.txt

rm encounter.o inventory.o Project04 
make 
# make clean
# make


dispValgrind(){
        [ ! -f "$_valgrindFile" ] && { echo "Error: $_valgrindFile file not found."; exit 2; }
        
        if [ -s "$_valgrindFile" ] 
        then
                echo "Displaying $_project_file:"
                echo "$(<$_valgrindFile)"
                # do something as file has data
        fi
}

checkOutput(){
        [ ! -f "$_test_file" ] && { echo "Error: $_test_file file not found."; exit 2; }
        
        if [ -s "$_test_file" ] 
        then
                echo "$_project_file is incorrect.  Differences are:"
                echo "$(<$_test_file)"
                # do something as file has data
        else
                echo "$_project_file is valid"
                # do something as file is empty 
        fi
}


checkAll(){

        valgrind --leak-check=full --demangle=yes --log-file=valgrind_1.txt $projectName ./input_1.txt > out1.txt
        valgrind --leak-check=full --log-file="valgrind_2.txt" $projectName ./input_2.txt > out2.txt
        valgrind --leak-check=full --log-file="valgrind_3.txt" $projectName ./input_3.txt > out3.txt
        valgrind --leak-check=full --log-file="valgrind_4.txt" $projectName ./input_4.txt > out4.txt
        valgrind --leak-check=full --log-file="valgrind_5.txt" $projectName ./input_5.txt > out5.txt


        sdiff -bBWs output_1.txt out1.txt > tmp1.txt
        sdiff -bBWs output_2.txt out2.txt > tmp2.txt
        sdiff -bBWs output_3.txt out3.txt > tmp3.txt
        sdiff -bBWs output_4.txt out4.txt > tmp4.txt
        sdiff -bBWs output_5.txt out5.txt > tmp5.txt

        echo "Checking your output files"
        _test_file="tmp1.txt"
        _project_file="Output 1"
        _valgrindFile="valgrind_1.txt"
        # dispValgrind
        checkOutput

        _test_file="tmp2.txt"
        _project_file="Output 2"
        _valgrindFile="valgrind_2.txt"
        # dispValgrind
        checkOutput

        _test_file="tmp3.txt"
        _project_file="Output 3"
        _valgrindFile="valgrind_3.txt"
        # dispValgrind
        checkOutput

        _test_file="tmp4.txt"
        _project_file="Output 4"
        _valgrindFile="valgrind_4.txt"
        # dispValgrind
        checkOutput

        _test_file="tmp5.txt"
        _project_file="Output 5"
        _valgrindFile="valgrind_5.txt"
        # dispValgrind
        checkOutput

        # _test_file="tmp5.txt"
        # _project_file="Output 5"
        # checkOutput

        echo "Check the valgrind outputs under valgrind_#.txt"
        echo "You are looking for no leaks!"


        rm tmp1.txt out1.txt 
        rm tmp2.txt out2.txt 
        rm tmp3.txt out3.txt 
        rm tmp4.txt out4.txt 
        rm tmp5.txt out5.txt 
}

checkOne()
{
        echo "Testing $1"
        if [[ $1 > 5 ]] ; then
                echo "provided a value out of range, please select 1-4"
                echo "provided: $1"
                exit 0
        fi
        if [[ $1 < 1 ]] ; then
                echo "provided a value out of range"
                echo "provided: $1"
                exit 0
        fi


        # valgrind --leak-check=full --log-file="valgrind_1.txt" $projectName ./input_1.txt > out1.txt
        _projectFile="./input_$1.txt"
        _outfile="out$1.txt"
        _checkFile="output$1.txt"
        _tmpFile="tmp$1.txt"
        _vgFile="valgrind_$1.txt"
        _vgCheckFile="m_valgrind_$1.txt"

        # $projectName $_projectFile > $_outfile
        valgrind --leak-check=full --demangle=yes --log-file=$_vgFile $projectName $_projectFile > $_outfile
        sdiff -bBWs $_checkFile $_outfile > $_tmpFile

        echo "Checking project output"
        _test_file=$_tmpFile
        _project_file="Output $1"
        _valgrindFile=$_vgFile
        dispValgrind
        checkOutput

        echo "You are looking for no memory leaks above."


        rm $_outfile $_tmpFile 
}



if [[ $1 == "" ]]
then
echo 'checking All'
checkAll
exit 0
fi


# otherwise run our single output.
checkOne $1
