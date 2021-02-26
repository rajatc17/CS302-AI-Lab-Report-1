# Title     : TODO
# Objective : TODO
# Created by: rajat
# Created on: 22-02-2021

library(bnlearn)
library(caret)
course.grades<-read.table("2020_bn_nb_data.txt",head=TRUE)
course.grades<-lapply(course.grades,as.factor)
course.grades<-data.frame(course.grades)
course.grades.net<-hc(course.grades, score = "k2")
set.seed(100)
tIndex <- createDataPartition(course.grades$QP, p=0.7)$Resample1
train <- course.grades[tIndex, ]
trainda <- bn.fit(hc(train, score="k2"), train)
test <- course.grades[-tIndex, ]
predicted <- predict(trainda, node="QP", data=test)
tabletrain <- table(test$QP, predicted)
trainAcc = (tabletrain[1,1]+tabletrain[2,2])/sum(tabletrain)
print(round(cbind("Training Accuracy" =trainAcc), 4))

