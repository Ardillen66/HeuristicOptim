setwd("C:/Users/arnau/Documents/School/Projecten 16_17/Heuristic optimization/HeuristicOptim/results")

best.sol <- read.csv("bestSolutions.txt")

##########################################################################################################

#Iterative improvement:

#First, transpose, random
ii.f.t.r <- read.csv("ii-first-trans-rand.txt")
a.devs <- 100 * (ii.f.t.r$Solution - best.sol$BS) / best.sol$BS
a.ctSum <- sum(ii.f.t.r$CT) 
a.avgDev <- mean(a.devs)

#First, transpose, RZ
ii.f.t.rz <- read.csv("ii-first-trans-rz.txt")
b.devs <- 100 * (ii.f.t.rz$Solution - best.sol$BS) / best.sol$BS
b.ctSum <- sum(ii.f.t.rz$CT) 
b.avgDev <- mean(b.devs)

#Best, transpose, Random
ii.b.t.r <- read.csv("ii-best-trans-rand.txt")
c.devs <- 100 * (ii.b.t.r$Solution - best.sol$BS) / best.sol$BS
c.ctSum <- sum(ii.b.t.r$CT) 
c.avgDev <- mean(c.devs)

#Best, transpose, RZ
ii.b.t.rz <- read.csv("ii-best-trans-rz.txt")
d.devs <- 100 * (ii.b.t.rz$Solution - best.sol$BS) / best.sol$BS
d.ctSum <- sum(ii.b.t.rz$CT) 
d.avgDev <- mean(d.devs)

#First, exchange, Random
ii.f.e.r <- read.csv("ii-first-ex-rand.txt")
e.devs <- 100 * (ii.f.e.r$Solution - best.sol$BS) / best.sol$BS
e.ctSum <- sum(ii.f.e.r$CT) 
e.avgDev <- mean(e.devs)

#First, exchange, RZ
ii.f.e.rz <- read.csv("ii-first-ex-rz.txt")
f.devs <- 100 * (ii.f.e.rz$Solution - best.sol$BS) / best.sol$BS
f.ctSum <- sum(ii.f.e.rz$CT) 
f.avgDev <- mean(f.devs)

#First, insert, Random
ii.f.i.r <- read.csv("ii-first-ins-rand.txt")
g.devs <- 100 * (ii.f.i.r$Solution - best.sol$BS) / best.sol$BS
g.ctSum <- sum(ii.f.i.r$CT) 
g.avgDev <- mean(g.devs)

#First, insert, RZ
ii.f.i.rz <- read.csv("ii-first-insert-rz.txt")
h.devs <- 100 * (ii.f.i.rz$Solution - best.sol$BS) / best.sol$BS
h.ctSum <- sum(ii.f.i.rz$CT) 
h.avgDev <- mean(h.devs)

#Statistical tests
t.test (a.devs, b.devs, paired=T)$p.value
wilcox.test (a.devs, b.devs, paired=T)$p.value

t.test (c.devs, d.devs, paired=T)$p.value
wilcox.test (c.devs, d.devs, paired=T)$p.value

t.test (e.devs, f.devs, paired=T)$p.value
wilcox.test (e.devs, f.devs, paired=T)$p.value

t.test (g.devs, h.devs, paired=T)$p.value
wilcox.test (g.devs, h.devs, paired=T)$p.value

#########################################################################################################

#Variable Neighbourhood descent

#T->E->I, Random
vnd.tei.r <- read.csv("vnd-tei-random.txt")
i.devs <- 100 * (vnd.tei.r$Solution - best.sol$BS) / best.sol$BS
i.ctSum <- sum(vnd.tei.r$CT) 
i.avgDev <- mean(i.devs)

#T->E->I, RZ
vnd.tei.rz <- read.csv("vnd-tei-rz.txt")
j.devs <- 100 * (vnd.tei.rz$Solution - best.sol$BS) / best.sol$BS
j.ctSum <- sum(vnd.tei.rz$CT) 
j.avgDev <- mean(j.devs)

#T->I->E, Random
vnd.tie.r <- read.csv("vnd-tie-random.txt")
k.devs <- 100 * (vnd.tie.r$Solution - best.sol$BS) / best.sol$BS
k.ctSum <- sum(vnd.tie.r$CT) 
k.avgDev <- mean(k.devs)

#T->I->I, RZ
vnd.tie.rz <- read.csv("vnd-tie-rz.txt")
l.devs <- 100 * (vnd.tie.rz$Solution - best.sol$BS) / best.sol$BS
l.ctSum <- sum(vnd.tie.rz$CT) 
l.avgDev <- mean(l.devs)

#Statistical tests
t.test (i.devs, j.devs, paired=T)$p.value
wilcox.test (i.devs, j.devs, paired=T)$p.value


















