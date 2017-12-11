args = commandArgs(trailingOnly=TRUE)

spt <- strsplit(args[1], "/")[[1]][4]

dt <- read.csv(args[1], header=TRUE, sep=",")

meanBetter <- apply(dt[,(2:41)%%4==3], 1, mean)
meanSd <- apply(dt[,(2:41)%%4==3], 1, sd)

cat(spt, "mean", meanBetter, "\n")
cat(spt, "sd", meanSd, "\n")
