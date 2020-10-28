// clang-format off
// Must before any other include
#include <RcppArmadillo.h>
// clang-format on

#include "libKriging/OrdinaryKriging.hpp"

// [[Rcpp::export]]
Rcpp::List ordinary_kriging(const arma::vec &y,
                            const arma::mat &X,
                            std::string kernel,
                            std::string regmodel = "constant",
                            bool normalize = false) {
  auto start = std::chrono::system_clock::now();
  OrdinaryKriging* ok = new OrdinaryKriging(kernel);
//  ok->fit(y, X);  //, OrdinaryKriging::Parameters{0,false,nullptr,false},"ll","bfgs");

  std::vector<double> times = 
  ok->fit(y,
          X,
          OrdinaryKriging::RegressionModelUtils::fromString(regmodel),
          normalize);  //, OrdinaryKriging::Parameters{0,false,nullptr,false},"ll","bfgs");

  Rcpp::XPtr<OrdinaryKriging> impl_ptr(ok);
  auto end = std::chrono::system_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  elapsed /= 1e6;

  times.push_back(elapsed); // 5
  //Rcpp::NumericVector e = { elapsed };
  
  Rcpp::List obj;
  obj.attr("object") = impl_ptr;
  obj.attr("class") = "OrdinaryKriging";
  obj.attr("time") = times;
  return obj;
}

// [[Rcpp::export]]
Rcpp::List ordinary_kriging_model(Rcpp::List ordinaryKriging) {
  if (!ordinaryKriging.inherits("OrdinaryKriging"))
    Rcpp::stop("Input must be a OrdinaryKriging object.");
  SEXP impl = ordinaryKriging.attr("object");

  Rcpp::XPtr<OrdinaryKriging> impl_ptr(impl);

  return Rcpp::List::create(
      Rcpp::Named("theta") = impl_ptr->theta(),
      Rcpp::Named("sigma2") = impl_ptr->sigma2(),
      Rcpp::Named("X") = impl_ptr->X(),
      Rcpp::Named("centerX") = impl_ptr->centerX(),
      Rcpp::Named("scaleX") = impl_ptr->scaleX(),
      Rcpp::Named("y") = impl_ptr->y(),
      Rcpp::Named("centerY") = impl_ptr->centerY(),
      Rcpp::Named("scaleY") = impl_ptr->scaleY(),
      Rcpp::Named("regmodel") = OrdinaryKriging::RegressionModelUtils::toString(impl_ptr->regmodel()),
      Rcpp::Named("F") = impl_ptr->F(),
      Rcpp::Named("T") = impl_ptr->T(),
      Rcpp::Named("M") = impl_ptr->M(),
      Rcpp::Named("z") = impl_ptr->z(),
      Rcpp::Named("beta") = impl_ptr->beta());
}

// [[Rcpp::export]]
double ordinary_kriging_logLikelihood(Rcpp::List ordinaryKriging, arma::vec theta) {
  if (!ordinaryKriging.inherits("OrdinaryKriging"))
    Rcpp::stop("Input must be a OrdinaryKriging object.");
  SEXP impl = ordinaryKriging.attr("object");

  Rcpp::XPtr<OrdinaryKriging> impl_ptr(impl);

  return impl_ptr->logLikelihoodFun(theta);
}

// [[Rcpp::export]]
double ordinary_kriging_leaveOneOut(Rcpp::List ordinaryKriging, arma::vec theta) {
  if (!ordinaryKriging.inherits("OrdinaryKriging"))
    Rcpp::stop("Input must be a OrdinaryKriging object.");
  SEXP impl = ordinaryKriging.attr("object");

  Rcpp::XPtr<OrdinaryKriging> impl_ptr(impl);

  return impl_ptr->leaveOneOutFun(theta);
}

// [[Rcpp::export]]
arma::vec ordinary_kriging_leaveOneOutGrad(Rcpp::List ordinaryKriging, arma::vec theta) {
  if (!ordinaryKriging.inherits("OrdinaryKriging"))
    Rcpp::stop("Input must be a OrdinaryKriging object.");
  SEXP impl = ordinaryKriging.attr("object");

  Rcpp::XPtr<OrdinaryKriging> impl_ptr(impl);

  return impl_ptr->leaveOneOutGrad(theta);
}

// [[Rcpp::export]]
arma::vec ordinary_kriging_logLikelihoodGrad(Rcpp::List ordinaryKriging, arma::vec theta) {
  if (!ordinaryKriging.inherits("OrdinaryKriging"))
    Rcpp::stop("Input must be a OrdinaryKriging object.");
  SEXP impl = ordinaryKriging.attr("object");

  Rcpp::XPtr<OrdinaryKriging> impl_ptr(impl);

  return impl_ptr->logLikelihoodGrad(theta);
}

// [[Rcpp::export]]
Rcpp::List ordinary_kriging_predict(Rcpp::List ordinaryKriging, arma::mat X, bool stdev, bool cov) {
  if (!ordinaryKriging.inherits("OrdinaryKriging"))
    Rcpp::stop("Input must be a OrdinaryKriging object.");
  SEXP impl = ordinaryKriging.attr("object");

  Rcpp::XPtr<OrdinaryKriging> impl_ptr(impl);

  if (stdev & cov) {
    auto pred = impl_ptr->predict(X, true, true);
    return Rcpp::List::create(Rcpp::Named("mean") = std::get<0>(pred),
                              Rcpp::Named("stdev") = std::get<1>(pred),
                              Rcpp::Named("cov") = std::get<2>(pred));
  } else if (stdev & !cov) {
    auto pred = impl_ptr->predict(X, true, false);
    return Rcpp::List::create(Rcpp::Named("mean") = std::get<0>(pred), Rcpp::Named("stdev") = std::get<1>(pred));
  } else if (!stdev & cov) {
    auto pred = impl_ptr->predict(X, false, true);
    return Rcpp::List::create(Rcpp::Named("mean") = std::get<0>(pred), Rcpp::Named("cov") = std::get<2>(pred));
  } else if (!stdev & !cov) {
    auto pred = impl_ptr->predict(X, false, false);
    return Rcpp::List::create(Rcpp::Named("mean") = std::get<0>(pred));
  }

  // FIXME no default return
}

// [[Rcpp::export]]
arma::mat ordinary_kriging_simulate(Rcpp::List ordinaryKriging, int nsim, arma::mat X) {
  if (!ordinaryKriging.inherits("OrdinaryKriging"))
    Rcpp::stop("Input must be a OrdinaryKriging object.");
  SEXP impl = ordinaryKriging.attr("object");

  Rcpp::XPtr<OrdinaryKriging> impl_ptr(impl);

  return impl_ptr->simulate(nsim, X);
}
