#!/bin/bash
data="lennabw_small.jpg"
folderIn=".pics/source/"
fileIn="${folderIn}/${data}"

prefixOut="len"
folderOut=".pics/results/lennabw_small/"

exe="./mechanical_drawing"

gen=200000
elit=1
thread=2

for multType in 1 2 3 4;
do
    for depth in 2 7 11;
    do
        for pMult in 0.2 0.4 0.6 0.8;
        do
            for pCross in 0.8 0.6 0.4 0.2;
            do
                for pop in 2 4 8 16 32;
                do
                    if [$pop <= 8];
                    then
                        thread=$pop
                    else
                        thread=8
                    fi

                    subFolder="${prefixOut}_${exe}_${pop}_${elit}_${depth}_${pCross}_${pMult}_${multType}_${gen}_${thread}"
                    mkdir ${subFolder}

                    par="${exe} ${pop} ${elit} ${depth} ${pCross} ${pMult} ${multType} ${gen} ${thread}"
                    echo ${par}
                    time ${par} ${fileIn} ${folderOut}/${subfolder}/${prefix} > ${folderOut}/${subfolder}/iterations.txt
                done
            done
        done
    done
done
