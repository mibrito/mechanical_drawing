args = commandArgs(trailingOnly=TRUE)

dt <- read.table(args[1], header=FALSE)

plot(t(dt[1,3:203]))