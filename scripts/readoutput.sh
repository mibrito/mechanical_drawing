#!/bin/sh

statistics ()
{
  sed 's/_/ /g' | awk '
  BEGIN {
    print "execution,duration,better,worse,better_tree,worse_tree"
  }
  /200000/ {
    fBetter=$2
    fBetterTree=$3
    fWorse=$4
    fWorseTree=$5
  }
  /duration/ { print NR/203 "," $2 "," 'fBetter' "," 'fWorse' "," 'fBetterTree' "," 'fWorseTree' }
  '
}

combine ()
{
  sed 's/_/ /g' | awk '
  BEGIN {
    nExec=0
    nVals=0
  }
  /^[0-9]/ {
    fBetter[nExec "," $1]=$2
    fBetterTree[nExec "," $1]=$3
    fWorse[nExec "," $1]=$4
    fWorseTree[nExec "," $1]=$5
    nVals++
  }
  /duration/ {
    duration[nExec "," $1]=$2
    nExec++
  }
  END {
    print "gen,fBetter0,fWorse0,fBetterTree0,fWorseTree0,fBetter1,fWorse1,fBetterTree1,fWorseTree1,fBetter2,fWorse2,fBetterTree2,fWorseTree2,fBetter3,fWorse3,fBetterTree3,fWorseTree3,fBetter4,fWorse4,fBetterTree4,fWorseTree4,fBetter5,fWorse5,fBetterTree5,fWorseTree5,fBetter6,fWorse6,fBetterTree6,fWorseTree6,fBetter7,fWorse7,fBetterTree7,fWorseTree7,fBetter8,fWorse8,fBetterTree8,fWorseTree8,fBetter9,fWorse9,fBetterTree9,fWorseTree9"
    for(j=0; j<(nVals/nExec); j++) {
      line=""
      for (i=0; i<nExec; i++) {
        line = line "," fBetter[i "," j*1000] "," fWorse[i "," j*1000] "," fBetterTree[i "," j*1000] "," fWorseTree[i "," j*1000]
      }
      print j*1000 line
    }
  }
  '
}

case $1 in
statistics) statistics ;;
combine) combine ;;
*) echo "Opcao Invalida!" ;;
esac


