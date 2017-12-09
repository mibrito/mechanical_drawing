#!/bin/bash
data="lennabw_small.jpg"
folderIn="./pics/source"
fileIn="${folderIn}/${data}"

prefixOut="len"
folderOut="./pics/results/lennabw_small2"

exe="./mechanical_drawing"

gen=200000
elit=1
thread=4

depth=2
pMult=0.8
pCross=0.2
pop=8

multType=3

#for multType in 1 2 3 4;
#do
    #for depth in 2 7;
    #do
        #for pMult in 0.2 0.5 0.8;
        #do
        #    for pCross in 0.8 0.5 0.2;
        #    do
        #        for pop in 4 8 10;
        #        do
        #            if [ "$pop" -eq 10 ];
        #            then
        #                thread=5
        #            else
        #                thread=4
        #            fi
                    for nExec in {1..20};
                    do

                        subFolder="${prefixOut}_${pop}_${elit}_${depth}_${pCross}_${pMult}_${multType}_${gen}_${thread}_nExec_${nExec}"

                        if [ ! -d "${folderOut}/${subFolder}" ]; then
                            mkdir -p "${folderOut}/${subFolder}"

                                # Will enter here if $DIRECTORY exists, even if it contains spaces
                            par="${exe} ${pop} ${elit} ${depth} ${pCross} ${pMult} ${multType} ${gen} ${thread}"
                            echo ${par}
                            time ${par} "./pics/source/lennabw_small.jpg" ${folderOut}/${subFolder}/${prefixOut} > ${folderOut}/${subFolder}/iterations.txt

                        fi
                    done
               #done
        #    done
        #done
    #done
#done
