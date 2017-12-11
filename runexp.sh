#!/bin/bash
data="cameraman.png"
folderIn="./pics/source"
fileIn="${folderIn}/${data}"

prefixOut="cam"
folderOut="./pics/results/testPMut"

exe="./mechanical_drawing"

gen=200000
elit=1
thread=8

depth=2
pMult=0.2
pCross=0.4
pop=8

multType=3

for pMult in 0.4 0.6 0.8;
do
    subFolder="${prefixOut}_${pop}_${elit}_${depth}_${pCross}_${pMult}_${multType}_${gen}_${thread}"

    if [ ! -d "${folderOut}/${subFolder}" ]; then
        mkdir -p "${folderOut}/${subFolder}"

        # Will enter here if $DIRECTORY exists, even if it contains spaces
        par="${exe} ${pop} ${elit} ${depth} ${pCross} ${pMult} ${multType} ${gen} ${thread}"
        echo ${par}
        ${par} ${fileIn} ${folderOut}/${subFolder}/${prefixOut} > ${folderOut}/${subFolder}/iterations.txt
    fi
done
