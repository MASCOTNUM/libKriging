% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/methods.R
\name{Kriging}
\alias{Kriging}
\title{Build a "Kriging" object from libKriging.}
\usage{
Kriging(
  y,
  X,
  kernel,
  regmodel = "constant",
  normalize = FALSE,
  optim = "BFGS",
  objective = "LL",
  parameters = NULL
)
}
\arguments{
\item{y}{Array of response values}

\item{X}{Matrix of input design}

\item{kernel}{Covariance model: "gauss", "exp", ...}

\item{regmodel}{Universal Kriging linear trend: "constant", "linear", "interactive" ("constant" by default)}

\item{normalize}{Normalize X and y in [0,1] (FALSE by default)}

\item{optim}{Optimization method to fit hyper-parameters: "BFGS", "Newton" (uses objective Hessian), "none" (keep initial "parameters" values)}

\item{objective}{Objective function to optimize: "LL" (log-Likelihood, by default), "LOO" (leave one out)}

\item{parameters}{Initial hyper parameters: list(sigma2=..., theta=...). If theta has many rows, each is used as a starting point for optim.}
}
\value{
S3 Kriging object. Should be used with its predict, simulate, update methods.
}
\description{
Build a "Kriging" object from libKriging.
}
\author{
Yann Richet (yann.richet@irsn.fr)
}
