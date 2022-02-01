library(ggplot2)

data<-read.table("Trajektorie.txt",sep=',',header=TRUE)
ggplot(data, aes(x=x, y=y, group=typ, colour=color)) + geom_line() + labs(x="x", y="y") 

a<-subset(data, data$x==0.001)
b<-subset(data, data$x==0.002)
ggplot(b, aes(x=a$y, y=y, group=typ, colour=color)) + geom_point() + labs(x="W1", y="W2") 
