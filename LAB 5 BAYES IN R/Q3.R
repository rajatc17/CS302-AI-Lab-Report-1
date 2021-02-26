# Title     : TODO
# Objective : TODO
# Created by: rajat
# Created on: 22-02-2021

library(bnlearn)
grades <- c("AA", "AB", "BB", "BC", "CC", "CD", "DD", "F")
course.grades<-read.table("2020_bn_nb_data.txt",head=TRUE)
course.grades<-lapply(course.grades,as.factor)
course.grades<-data.frame(course.grades)
course.grades.net<-hc(course.grades,score = "k2")
course.grades.net.fit <- bn.fit(course.grades.net, course.grades )

prob <- 0.0
ans = ""
for(value in grades) {
  p <- cpquery(course.grades.net.fit, event = (PH100== value), evidence = (EC100=="DD" & IT101=="CC" & MA101=="CD"))
  if(p > prob) {
    ans <- value
    prob <- p
  }
}
print(ans)
