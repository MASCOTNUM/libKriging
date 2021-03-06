% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/methods.R
\name{update.Kriging}
\alias{update.Kriging}
\alias{update,Kriging,Kriging-method}
\title{Update Kriging model with new points}
\usage{
\method{update}{Kriging}(object, newy, newX, normalize = FALSE, ...)
}
\arguments{
\item{object}{S3 Kriging object}

\item{newy}{new points in model output space}

\item{newX}{new points in model input space}

\item{normalize}{Normalize X and y in [0,1] (FALSE by default)}

\item{...}{Ignored}
}
\description{
Update Kriging model with new points
}
\examples{
f = function(x) 1-1/2*(sin(12*x)/(1+x)+2*cos(7*x)*x^5+0.7)
  plot(f)
set.seed(123)
X <- as.matrix(runif(5))
y <- f(X)
  points(X,y,col='blue')
r <- Kriging(y, X, "gauss")
x = seq(0,1,,101)
p_x = predict(r, x)
  lines(x,p_x$mean,col='blue')
  lines(x,p_x$mean-2*p_x$stdev,col='blue')
  lines(x,p_x$mean+2*p_x$stdev,col='blue')
newX <- as.matrix(runif(3))
newy <- f(newX)
  points(newX,newy,col='red')
update(r,newy,newX)
x = seq(0,1,,101)
p2_x = predict(r, x)
  lines(x,p2_x$mean,col='red')
  lines(x,p2_x$mean-2*p2_x$stdev,col='red')
  lines(x,p2_x$mean+2*p2_x$stdev,col='red')
}
\author{
Yann Richet (yann.richet@irsn.fr)
}
