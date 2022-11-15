dyn.load("build/lib/libvsl_wrapper.so")
kml_runif<-function(len, min, max, kind) {
    y<-.C("kml_runif", as.integer(len), res=as.double(1:len), as.double(min), as.double(max),as.integer(kind))$res
    return(y)
}
kml_rbeta<-function(len, aa, bb, kind) {
    y<-.C("kml_rbeta", as.integer(len), res=as.double(1:len), as.double(aa), as.double(bb),as.integer(kind))$res
    return(y)
}
kml_rbinom<-function(len, size, prob, kind) {
    y<-.C("kml_rbinom", as.integer(len), res=as.integer(1:len), as.integer(size), as.double(prob),as.integer(kind))$res
    return(y)
}
kml_rcauchy<-function(len, location, scale, kind) {
    y<-.C("kml_rcauchy", as.integer(len), res=as.double(1:len), as.double(location), as.double(scale),as.integer(kind))$res
    return(y)
}
kml_rexp<-function(len, rate, kind) {
    y<-.C("kml_rexp", as.integer(len), res=as.double(1:len), as.double(rate),as.integer(kind))$res
    return(y)
}
kml_rgamma<-function(len, shape, scale, kind) {
    y<-.C("kml_rgamma", as.integer(len), res=as.double(1:len), as.double(shape), as.double(scale),as.integer(kind))$res
    return(y)
}
kml_rgeom<-function(len, p, kind) {
    y<-.C("kml_rgeom", as.integer(len), res=as.integer(1:len), as.double(p),as.integer(kind))$res
    return(y)
}
kml_rhyper<-function(len, m, n, k, kind) {
    y<-.C("kml_rhyper", as.integer(len), res=as.integer(1:len), as.integer(m), as.integer(n), as.integer(k),as.integer(kind))$res
    return(y)
}
kml_rlnorm<-function(len, meanlog, sdlog, kind) {
    y<-.C("kml_rlnorm", as.integer(len), res=as.double(1:len), as.double(meanlog), as.double(sdlog),as.integer(kind))$res
    return(y)
}
kml_rnbinom<-function(len, size, mu, kind) {
    y<-.C("kml_rnbinom", as.integer(len), res=as.integer(1:len), as.integer(size), as.double(mu),as.integer(kind))$res
    return(y)
}
kml_rnorm<-function(len, mu, sigma, kind) {
    y<-.C("kml_rnorm", as.integer(len), res=as.double(1:len), as.double(mu), as.double(sigma),as.integer(kind))$res
    return(y)
}
kml_rpois<-function(len, mu, kind) {
    y<-.C("kml_rpois", as.integer(len), res=as.integer(1:len), as.double(mu),as.integer(kind))$res
    return(y)
}
kml_rweibull<-function(len, shape, scale, kind) {
    y<-.C("kml_rweibull", as.integer(len), res=as.double(1:len), as.double(shape), as.double(scale),as.integer(kind))$res
    return(y)
}
kml_rng_kind<-function(kind) {
    y<-.C("kml_rng_kind", as.integer(kind))
}
kml_set_seed<-function(seed) {
    y<-.C("kml_set_seed", as.integer(seed))
}