# Title     : TODO
# Objective : TODO
# Created by: rajat
# Created on: 22-02-2021

library(bnlearn)
course.grades<-read.table("2020_bn_nb_data.txt",head=TRUE)
course.grades<-lapply(course.grades,as.factor)
course.grades<-data.frame(course.grades)
course.grades.net<-hc(course.grades,score = "k2")

course.grades.net.fit <- bn.fit(course.grades.net, course.grades )
bn.fit.barchart(course.grades.net.fit$EC100)
bn.fit.barchart(course.grades.net.fit$EC160)
bn.fit.barchart(course.grades.net.fit$IT101)
bn.fit.barchart(course.grades.net.fit$IT161)
bn.fit.barchart(course.grades.net.fit$MA101)
bn.fit.barchart(course.grades.net.fit$PH100)
bn.fit.barchart(course.grades.net.fit$HS101)
bn.fit.barchart(course.grades.net.fit$QP)
print(course.grades.net.fit)
