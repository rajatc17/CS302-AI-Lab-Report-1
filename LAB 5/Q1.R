# Title     : TODO
# Objective : TODO
# Created by: rajat
# Created on: 22-02-2021
library(bnlearn)
course.grades<-read.table("2020_bn_nb_data.txt",head=TRUE)
course.grades<-lapply(course.grades,as.factor)
course.grades<-data.frame(course.grades)
course.grades.net<-hc(course.grades,score = "k2")
plot(course.grades.net)